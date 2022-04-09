#include "include/cond.h"

Practice::Cond::Cond() { pthread_cond_init(&this->cond, NULL); }

Practice::Cond::~Cond() { pthread_cond_destroy(&this->cond); }

void Practice::Cond::wait(pthread_mutex_t *mutex) {
    pthread_cond_wait(&this->cond, mutex);
}

void Practice::Cond::signal() {
    pthread_cond_signal(&this->cond);
}