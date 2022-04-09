#pragma once
#include <list>

#include "task.h"
#include "thread.h"

namespace Practice {
class ThreadPool {
 public:
  ThreadPool();
  ~ThreadPool();
  void addTask(Task *task);
  void init(int maxThreads);

 private:
  int maxThreads;
  std::list<WorkThread *> mPool;
  std::list<Task *> mTaskQueue;
  ManageThread *mManageThread;
};

}  // namespace Practice