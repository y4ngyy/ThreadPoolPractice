#include "include/thread_work.h"

#include <iostream>

#include "include/thread_manage.h"

Practice::WorkThread::WorkThread(ManageThread *manager) {
  mManager = manager;
  mIsFinish = false;
}

Practice::WorkThread::~WorkThread() {
  std::cout << "WorkThread deconstruct" << '\n';
}

void Practice::WorkThread::run() {
  Task *task = NULL;
  while (true) {
    mIsBusy = false;
    if (mIsFinish) break;
    mManager->notifyIdle();
    task = getTask();
    mIsBusy = true;
    try {
      task->run();
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
  pthread_exit(NULL);
}

bool Practice::WorkThread::isBusy() { return this->mIsBusy; }
