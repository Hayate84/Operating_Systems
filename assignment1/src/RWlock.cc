#include "RWlock.h"

RWlock::RWlock() {

  pthread_mutex_init(&mtx, NULL);

  pthread_cond_init(&readersVar, NULL);
  pthread_cond_init(&writersVar, NULL);

  readersNum   = 0;
  writerActive = false;
  isEmpty = true;
}

RWlock::~RWlock() {
  pthread_mutex_destroy(&mtx);

  pthread_cond_destroy(&readersVar);
  pthread_cond_destroy(&writersVar);
}

void RWlock::writerCsEnter() {
  pthread_mutex_lock(&mtx);
  while(isEmpty == false) {
    pthread_cond_wait(&writersVar, &mtx);
  }
  pthread_mutex_unlock(&mtx);
}

void RWlock::writerCsExit() {
  pthread_mutex_lock(&mtx);
  isEmpty = false;
  pthread_cond_broadcast(&readersVar);
  pthread_mutex_unlock(&mtx);
}

void RWlock::readerCsEnter() {
  pthread_mutex_lock(&mtx);
  while(isEmpty == true) {
    pthread_cond_wait(&readersVar, &mtx);
  }
  readersNum = readersNum + 1;
  pthread_mutex_unlock(&mtx);
}

void RWlock::readerCsExit() {
  pthread_mutex_lock(&mtx);
  readersNum = readersNum - 1;
  if (readersNum == 0) {
    isEmpty = true;
    pthread_cond_signal(&writersVar);
  }
  pthread_mutex_unlock(&mtx);
}
