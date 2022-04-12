#include "include/cond.h"

Practice::Cond::Cond() { pthread_cond_init(&this->cond, NULL); }

Practice::Cond::~Cond() { pthread_cond_destroy(&this->cond); }

void Practice::Cond::wait(pthread_mutex_t *mutex) {
  pthread_cond_wait(&this->cond, mutex);
}

void Practice::Cond::signal() { pthread_cond_signal(&this->cond); }

// !这种写法可能还存在问题
void Practice::Cond::timedWait(pthread_mutex_t *mutex, int timeOut) {
  clock_gettime(CLOCK_REALTIME, &to);
  to.tv_sec += timeOut;
  pthread_cond_timedwait(&this->cond, mutex, &to);
}