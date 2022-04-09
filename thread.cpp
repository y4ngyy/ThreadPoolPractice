#include "include/thread.h"

#include <iostream>

Practice::Thread::Thread() {}

bool Practice::Thread::start() {
  return pthread_create(&this->id, NULL, threadFunc, (void *)this) == 0;
}

void *Practice::Thread::threadFunc(void *arg) {
  Thread *self = (Thread *)arg;
  self->run();
  return NULL;
}

// consumer
Practice::WorkThread::WorkThread(ManageThread *manager) {
  mManager = manager;
}

void Practice::WorkThread::run() {
  Task *task = NULL;
  mIsBusy = false;
  while (true) {
    pthread_mutex_lock(&mMutex);
    while (mTaskQueue.empty()) {
      mIsBusy = false;
      // 通知ManageThread空闲 条件变量Idle需要加锁
      mManager->notifyIdle();
      mTaskQueueEmpty.wait(&mMutex);
    }
    task = mTaskQueue.front();
    mTaskQueue.pop_front();
    mIsBusy = true;
    pthread_mutex_unlock(&mMutex);
    try {
      task->run();
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
}

// MainThread、ManageThread调用
void Practice::WorkThread::addTask(Task *task) {
  pthread_mutex_lock(&mMutex);
  mTaskQueue.push_back(task);
  notify();
  pthread_mutex_unlock(&mMutex);
}

bool Practice::WorkThread::isBusy() { return this->mIsBusy; }

void Practice::WorkThread::notify() { mTaskQueueEmpty.signal(); }

Practice::ManageThread::ManageThread(std::list<WorkThread *> *pool,
                                     std::list<Task *> *taskQueue,
                                     int maxThreads) {
  mPool = pool;
  mTaskQueue = taskQueue;
  mMaxThreads = maxThreads;
}

void Practice::ManageThread::run() {
  Task *task = NULL;
  while (true) {
    // 等待任务放入
    pthread_mutex_lock(&mMutex);
    while (mTaskQueue->empty()) {
      mTaskQueueEmpty.wait(&mMutex);
    }
    // 把等待的任务放到工作线程中
    task = mTaskQueue->front();
    mTaskQueue->pop_front();
    pthread_mutex_unlock(&mMutex);
    while (!findIdleThreadAndAddTask(task)) {
      // 没有找到空闲的工作线程，进入等待状态
      pthread_mutex_lock(&mThreadBusyMutex);
      mAllThreadsBusy.wait(&mThreadBusyMutex);
      pthread_mutex_unlock(&mThreadBusyMutex);
    }
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
    (*it)->addTask(task);  // addTask中有同步操作
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
    t->start();  // start后进入等待状态
    t->addTask(task);
    // 这里需要通知一下线程开始
    mPool->push_back(t);  // Pool只有MainThread操作，不是竞争资源
    return;
  }

  // 线程池中工作线程数量已达上限，放入等待队列
  pthread_mutex_lock(&mMutex);
  mTaskQueue->push_back(task);
  mTaskQueueEmpty.signal();
  pthread_mutex_unlock(&mMutex);
}

void Practice::ManageThread::notifyIdle() {
  pthread_mutex_lock(&mThreadBusyMutex);
  mAllThreadsBusy.signal();
  pthread_mutex_unlock(&mThreadBusyMutex);
}
