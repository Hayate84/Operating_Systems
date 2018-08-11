#ifndef __PCLOCK__
#define __PCLOCK__

#include <pthread.h>

class PClock {
private:
  pthread_mutex_t mtx;

  pthread_cond_t prod_cond;
  pthread_cond_t cons_cond;

  bool empty;
  bool full;

  int data;
  int threads;
  int threadsMax;

public:
  PClock(int threadsMax);
  ~PClock();

  int get();
  void set(int data);
};

#endif
