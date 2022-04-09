#pragma once
#include <pthread.h>

namespace Practice {
class Cond {
 private:
  pthread_cond_t cond;

 public:
  Cond();
  ~Cond();
  void wait(pthread_mutex_t *);
  void signal();
};
}  // namespace Practice