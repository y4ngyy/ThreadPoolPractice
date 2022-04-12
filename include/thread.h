#pragma once
#include <pthread.h>


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



}  // namespace Practice
