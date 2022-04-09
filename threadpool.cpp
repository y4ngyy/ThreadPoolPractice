#include "include/threadpool.h"

Practice::ThreadPool::ThreadPool() : maxThreads(10) {}

Practice::ThreadPool::~ThreadPool() {}

void Practice::ThreadPool::init(int initThreadsNum) {
  if (initThreadsNum > maxThreads) initThreadsNum = maxThreads;
  // 线程池初始化时先启动ManageThread
  if (mManageThread == NULL) {
    mManageThread = new ManageThread(&mPool, &mTaskQueue, maxThreads);
  }
  mManageThread->start();
  // 添加WorkThread
  for (int i = 0; i < initThreadsNum; i++) {
    WorkThread *t = new WorkThread(mManageThread);
    t->start();
    mPool.push_back(t);
  }
}

void Practice::ThreadPool::addTask(Task *task) { mManageThread->addTask(task); }