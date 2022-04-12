#pragma once
#include <pthread.h>
#include <time.h>

namespace Practice {
class Cond {
 private:
  pthread_cond_t cond;
  timespec to;
 public:
  Cond();
  ~Cond();
  void wait(pthread_mutex_t *);
  void timedWait(pthread_mutex_t *, int);
  void signal();
};
}  // namespace Practice