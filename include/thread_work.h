#pragma once
#include "thread_manage.h"
#include "thread_taskqueue.h"

namespace Practice {
class ManageThread;
class WorkThread : public TaskQueueThread {
 public:
  virtual void run();
  void addTask(Task *task);
  bool isBusy();
  WorkThread(ManageThread *);
  ~WorkThread();

 private:
  bool mIsBusy;
  Cond mTaskQueueEmpty;
  pthread_mutex_t mMutex;
  ManageThread *mManager;
};
}  // namespace Practice