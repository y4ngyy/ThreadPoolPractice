#include "include/threadpool.h"

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
  //销毁流程
  
}

void Practice::ThreadPool::addTask(Task *task) { mManageThread->addTask(task); }