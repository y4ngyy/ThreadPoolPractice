#include <iostream>

#include "include/thread_work.h"
#include "include/thread_manage.h"


Practice::WorkThread::WorkThread(ManageThread *manager) {
  mManager = manager;
  mIsFinish = false;
}

Practice::WorkThread::~WorkThread() {

}

void Practice::WorkThread::run() {
  Task *task = NULL;
  mIsBusy = false;
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
