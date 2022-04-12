#include "include/thread_manage.h"

#include <iostream>

#include "include/thread_work.h"

Practice::ManageThread::ManageThread(std::list<WorkThread *> *pool,
                                     int maxThreads)
    : TIME_WAIT(1000) {
  mPool = pool;
  mMaxThreads = maxThreads;
}

Practice::ManageThread::~ManageThread() {}

void Practice::ManageThread::run() {
  Task *task = NULL;
  while (true) {
    // todo 工作线程在闲时能够回收一些线程

    task = getTask();  // 从任务队列中获取任务，队列空则进入睡眠

    pthread_mutex_lock(&mThreadBusyMutex);
    while (!findIdleThreadAndAddTask(task)) {
      // 没有找到空闲的工作线程，进入等待状态
      // *使用timeWait防止和工作线程相互等待死锁
      mAllThreadsBusy.timedWait(&mThreadBusyMutex, TIME_WAIT);
    }
    pthread_mutex_unlock(&mThreadBusyMutex);
  }
}

// 成功找到空闲线程放入任务返回true 否则返回false
bool Practice::ManageThread::findIdleThreadAndAddTask(Task *task) {
  // 每个线程的TaskQueue为竞争资源
  // MainThread、ManageThread、自身
  for (std::list<WorkThread *>::iterator it = mPool->begin();
       it != mPool->end(); it++) {
    if ((*it)->isBusy()) {
      continue;
    }
    (*it)->addTaskAndNotify(task);  // addTask中有同步操作
    return true;
  }
  return false;
}

// MainThread调用
void Practice::ManageThread::addTask(Task *task) {
  // 找到空闲线程，放入任务
  if (findIdleThreadAndAddTask(task)) {
    return;
  }

  // 工作线程不足的时候新开线程执行
  if (mPool->size() < mMaxThreads) {
    WorkThread *t = new WorkThread(this);
    t->start();           // start后进入等待状态
    mPool->push_back(t);  // Pool只有MainThread做写操作，不是竞争资源
    t->addTaskAndNotify(task);
    return;
  }

  // 线程池中工作线程数量已达上限，放入等待队列
  addTaskAndNotify(task);
}

// WorkThread调用通知管理线程
void Practice::ManageThread::notifyIdle() {
  pthread_mutex_lock(&mThreadBusyMutex);
  mAllThreadsBusy.signal();
  pthread_mutex_unlock(&mThreadBusyMutex);
}
