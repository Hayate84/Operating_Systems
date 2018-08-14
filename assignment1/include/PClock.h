#ifndef __PCLOCK__
#define __PCLOCK__

#include <pthread.h>

/***************************************
 * Producer Consumer Lock              *
 * The design is based on the instance *
 * one Producer n Consumers.           *
 ***************************************/

class PClock {
private:
  pthread_mutex_t mtx;

  pthread_cond_t prod_cond;
  pthread_cond_t cons_cond;

  bool empty;

  int data; // The shared data is one integer
  int threads;
  int threadsMax;

public:
  PClock(int threadsMax);
  ~PClock();

  int get();          // Consume
  void set(int data); // Produce
};

#endif
