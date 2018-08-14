#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "printFunctions.h"
#include "PClock.h"
#include "Init.h"

#define FILENAMESIZE 30
#define NUMBERSIZE 20
#define MAINTHREADNAME "./logs/Thread_main"
#define PREFIX "logs/Thread_"

pthread_barrier_t barr;

// The Arguments for the Thread
// Shared resources
struct Args {
  PClock * lock;
  int arraySize;
};

void * func_t(void * args) {
  Args * a = (Args *) args;
  int size = a->arraySize;

  int * array;
  if ((array = (int *) calloc(a->arraySize, sizeof(int))) == NULL) {
    perror("Not enough memory.");
    exit(EXIT_FAILURE);
  }

  // Get the shared data
  // Stop using a barrier until all threads get the shared data
  for (int i = 0; i < size; i++) {
    array[i] = a->lock->get();
    pthread_barrier_wait(&barr);
  }

  // Make log
  char fileName[FILENAMESIZE];
  char num[NUMBERSIZE];

  strcpy(fileName, PREFIX);
  sprintf(num, "%li", pthread_self());
  strcat(fileName, num);
  print_array_to_file(array, a->arraySize, fileName, 3);

  free(array);
}

int main(int argc, char **argv) {
  Init init(argc, argv);

  int * array = new int[init.arraySize];
  for (int i = 0; i < init.arraySize; ++i) array[i] = rand() % 1000;

  pthread_barrier_init(&barr, NULL, init.threadsNum);

  PClock * lock = new PClock(init.threadsNum);

  Args * a      = new Args();
  a->arraySize  = init.arraySize;
  a->lock       = lock;

  pthread_t * threadArray = new pthread_t[init.threadsNum];

  for (int i = 0; i < init.threadsNum; i++) pthread_create(&threadArray[i], NULL, func_t, a);

  // Produce a value of the array as a shared resource
  for (int i = 0; i < init.arraySize; i++) a->lock->set(array[i]);

  char main[] = MAINTHREADNAME;
  print_array_to_file(array, a->arraySize, main, 3);

  for (int i = 0; i < init.threadsNum; i++) pthread_join(threadArray[i], NULL);

  delete lock;              delete a;
  delete[] threadArray;     delete[] array;

  exit(EXIT_SUCCESS);
}
