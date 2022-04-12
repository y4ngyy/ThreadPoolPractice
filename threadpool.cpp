#include "include/threadpool.h"

#include <unistd.h>

#include <iostream>

Practice::ThreadPool::ThreadPool(int initThreadsNum, int maxThreadsNum) {
  if (initThreadsNum > maxThreadsNum) initThreadsNum = maxThreadsNum;
  mMaxThreadsNum = maxThreadsNum;
  // 线程池初始化时先启动ManageThread
  if (mManageThread == NULL) {
    mManageThread = new ManageThread(&mPool, mMaxThreadsNum);
  }
  mManageThread->start();
  // 添加WorkThread
  for (int i = 0; i < initThreadsNum; i++) {
    WorkThread *t = new WorkThread(mManageThread);
    t->start();
    mPool.push_back(t);
  }
}

Practice::ThreadPool::~ThreadPool() {
  // 停止管理线程
  mManageThread->cancel();
  // 停止工作线程
  for (std::list<WorkThread *>::iterator iter = mPool.begin();
       iter != mPool.end(); iter++) {
    if ((*iter)->isBusy()) {
      // 线程还有任务未执行完毕则发出信号等待执行完毕
      (*iter)->notifyFinish();
    } else {
      (*iter)->cancel();
    }
  }
  sleep(5);
  // 释放内存
  delete mManageThread;
  std::cout << "ManageThread free" << '\n';
  for (std::list<WorkThread *>::iterator iter = mPool.begin();
       iter != mPool.end(); iter++) {
    delete *iter;
    // mPool.erase(iter); 有问题
  }
  mPool.clear();
}

void Practice::ThreadPool::addTask(Task *task) { mManageThread->addTask(task); }