#include "RWlock.h"

RWlock::RWlock() {
  pthread_mutex_init(mtx, NULL);

  pthread_cond_init(readersVar, NULL);
  pthread_cond_init(writersVar, NULL);

  readersNum   = 0;
  writerActive = false;
}

RWlock::~RWlock() {
  pthread_mutex_destroy(mtx);

  pthread_cond_destroy(readersVar);
  pthread_cond_destroy(writersVar);
}

void RWlock::writerCsEnter() {
  pthread_mutex_lock(mtx);
  while(writerActive == true || readersNum > 0) {
    pthread_cond_wait(writersVar, mtx);
  }
  writerActive = true;
  pthread_mutex_unlock(mtx);
}

void RWlock::readerCsEnter() {
  pthread_mutex_lock(mtx);
  while(writerActive == true) {
    pthread_cond_wait(readersVar, mtx);
  }
  readersNum = readersNum + 1;
  pthread_mutex_unlock(mtx);
}

void RWlock::writerCsExit() {
  pthread_mutex_lock(mtx);
  writerActive = false;
  pthread_cond_broadcast(readersVar);
  pthread_mutex_unlock(mtx);
}

void RWlock::readerCsExit() {
 pthread_mutex_lock(mtx);
 readersNum = readersNum - 1;
 if (readersNum == 0) {
   pthread_cond_signal(writersVar);
 }
  pthread_mutex_unlock(mtx);
}
