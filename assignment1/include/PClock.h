#ifndef __RWLOCK__
#define __RWLOCK__

#include <pthread.h>

class RWlock {
private:
  pthread_mutex_t mtx;

  pthread_cond_t writersVar;
  pthread_cond_t readersVar;

  int readersNum;
  bool writerActive;
  bool isEmpty;

public:
  RWlock();
  ~RWlock();

  void writerCsEnter();
  void readerCsEnter();

  void writerCsExit();
  void readerCsExit();
};

#endif
