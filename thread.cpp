#include "include/thread.h"

#include <iostream>

Practice::Thread::Thread() {}

Practice::Thread::~Thread() {}

bool Practice::Thread::start() {
  return pthread_create(&this->id, NULL, threadFunc, (void *)this) == 0;
}

void *Practice::Thread::threadFunc(void *arg) {
  Thread *self = (Thread *)arg;
  self->run();
  return NULL;
}