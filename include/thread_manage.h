#pragma once
#include "thread_taskqueue.h"
#include "thread_work.h"

namespace Practice {
class WorkThread;
class ManageThread : public TaskQueueThread {
 public:
  ManageThread(std::list<WorkThread *> *pool, int maxThreads);
  ~ManageThread();
  virtual void run();
  void addTask(Task *task);
  void notifyIdle();  // 工作线程调用
 private:
  int mMaxThreads;
  std::list<WorkThread *> *mPool;
  pthread_mutex_t mThreadBusyMutex;
  Cond mAllThreadsBusy;
  const int TIME_WAIT;  // 当所有线程为忙碌状态时，睡眠等待的时间 ms
  bool findIdleThreadAndAddTask(Task *task);
};
}