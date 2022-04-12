#include "include/thread_taskqueue.h"

Practice::TaskQueueThread::TaskQueueThread() {
  pthread_mutex_init(&mMutex, NULL);
}

Practice::TaskQueueThread::~TaskQueueThread() {
  pthread_mutex_destroy(&mMutex);
}

void Practice::TaskQueueThread::addTaskAndNotify(Task *task) {
  pthread_mutex_lock(&mMutex);
  mTaskQueue.push_back(task);
  mTaskQueueEmpty.signal();
  pthread_mutex_unlock(&mMutex);
}

Practice::Task *Practice::TaskQueueThread::getTask() {
  pthread_mutex_lock(&mMutex);
  while (mTaskQueue.empty()) {
    mTaskQueueEmpty.wait(&mMutex);
  }
  Task *task = mTaskQueue.front();
  mTaskQueue.pop_front();
  pthread_mutex_unlock(&mMutex);
  return task;
}