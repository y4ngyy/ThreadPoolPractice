#include <pthread.h>

#include <list>

#include "cond.h"
#include "task.h"

namespace Practice {
class Thread {
 public:
  Thread();
  ~Thread();
  bool start();
  virtual void run() = 0;
  static void *threadFunc(void *);

 private:
  pthread_t id;
};

class WorkThread : public Thread {
 public:
  virtual void run();
  void addTask(Task *task);
  bool isBusy();
  WorkThread(ManageThread *);

 private:
  bool mIsBusy;
  Cond mTaskQueueEmpty;
  pthread_mutex_t mMutex;
  ManageThread *mManager;
  std::list<Task *> mTaskQueue;

  void notify(); // notify在相应的功能函数中调用
};

class ManageThread : public Thread {
 public:
  ManageThread(std::list<WorkThread *> *pool, std::list<Task *> *taskQueue,
               int maxThreads);
  ~ManageThread();
  virtual void run();
  void addTask(Task *task);
  void notifyIdle(); // 工作线程调用
 private:
  int mMaxThreads;
  std::list<WorkThread *> *mPool;
  pthread_mutex_t mMutex;
  pthread_mutex_t mThreadBusyMutex;
  Cond mTaskQueueEmpty;
  Cond mAllThreadsBusy;
  std::list<Task *> *mTaskQueue;

  bool findIdleThreadAndAddTask(Task *task);
};
}  // namespace Practice
