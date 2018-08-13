#include "PClock.h"

PClock::PClock(int threadsMax) {

  pthread_mutex_init(&mtx, NULL);

  pthread_cond_init(&prod_cond, NULL);
  pthread_cond_init(&cons_cond, NULL);

  threads = 0;
  this->threadsMax = threadsMax;

  empty = true;
  full  = false;
}

PClock::~PClock() {
  pthread_mutex_destroy(&mtx);

  pthread_cond_destroy(&prod_cond);
  pthread_cond_destroy(&cons_cond);
}

int PClock::get() {
  pthread_mutex_lock(&mtx);
  while(empty == true) {
    pthread_cond_wait(&cons_cond, &mtx);
  }

  threads = threads + 1;

  if (threads == threadsMax) {
    threads = 0;
    empty = true;
    pthread_cond_signal(&prod_cond);
  }
  int rv = data;
  pthread_mutex_unlock(&mtx);

  pthread_cond_signal(&cons_cond);
  return rv;
}

void PClock::set(int data) {
  pthread_mutex_lock(&mtx);
  while (empty == false) {
    pthread_cond_wait(&prod_cond, &mtx);
  }

  this->data = data;
  empty = false;

  pthread_cond_signal(&cons_cond);
  pthread_mutex_unlock(&mtx);
}
