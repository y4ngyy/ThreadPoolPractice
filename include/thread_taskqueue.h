#include <list>

#include "cond.h"
#include "task.h"
#include "thread.h"

namespace Practice {
class TaskQueueThread : public Thread {
 public:
  TaskQueueThread();
  ~TaskQueueThread();
  void addTaskAndNotify(Task *task);

 protected:
  Cond mTaskQueueEmpty;
  pthread_mutex_t mMutex;
  std::list<Task *> mTaskQueue;

  Task *getTask();
};
}  // namespace Practice