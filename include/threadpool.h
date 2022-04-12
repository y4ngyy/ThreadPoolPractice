#pragma once
#include <list>

#include "task.h"
#include "thread.h"
#include "thread_manage.h"
#include "thread_work.h"

namespace Practice {
class ThreadPool {
 public:
  ThreadPool(int, int);
  ~ThreadPool();
  void addTask(Task *task);

 private:
  int mMaxThreadsNum;
  std::list<WorkThread *> mPool;
  ManageThread *mManageThread;
};

}  // namespace Practice