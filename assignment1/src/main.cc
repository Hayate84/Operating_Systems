#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "RWlock.h"

#define SMALLEST_ARRAY_SIZE 3000

struct Args {
  RWlock * lock;
  int shared;
  int arraySize;
};

void * func_t(void * args) {
  Args * a = (Args *) args;

  int * array;
  if ((array = (int *) calloc(a->arraySize, sizeof(int))) == NULL) {
    perror("Not enough memory.");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < a->arraySize; i++) {
    a->lock->readerCsEnter();
    array[i] = a->shared;
    a->lock->readerCsExit();
  }

  free(array);
}

int main(int argc, char **argv) {

  // Invalid number of arguments
  if (argc != 3) {
    fprintf(stderr, "Error: Invalid number or arguments.\n");
    fprintf(stderr, " Please run with two. M > 3000 the size of the array");
    fprintf(stderr, " and N > 0 number of processes to be executed.\n");
    exit(EXIT_FAILURE);
  }

  // M the size of the array
  const int arraySize = atoi(argv[1]);

  // Invalid array size
  if (arraySize < SMALLEST_ARRAY_SIZE) {
    fprintf(stderr, "Error: Invalid array size.\n");
    fprintf(stderr, " Array size M must be > %d.\n", SMALLEST_ARRAY_SIZE);
    exit(EXIT_FAILURE);
  }

  // Number of consumer programs
  int threadsNum = atoi(argv[2]);
  if (threadsNum < 1) {
    fprintf(stderr, "Error: Invalid number of processes.\n");
    fprintf(stderr, " Number of process size N must be > 0.\n");
    exit(EXIT_FAILURE);
  }

  // Define the array
  int * array;
  if ((array = (int *) calloc(arraySize, sizeof(int))) == NULL) {
    perror("Not enough memory.");
    exit(EXIT_FAILURE);
  }

  // Init the array
  for (int i = 0; i < arraySize; ++i) {
    array[i] = i; // rand() % 1000;
  }

  RWlock * lock = new RWlock();
  Args * a = new Args();

  a->arraySize = arraySize;
  a->lock = lock;

  pthread_t *threadArray = (pthread_t *) malloc(threadsNum * sizeof(pthread_t));

  for (int i = 0; i < threadsNum; i++) {
    pthread_create(&threadArray[i], NULL, func_t, a);
  }

  for (int i = 0; i < arraySize; i++) {
    lock->writerCsEnter();
    a->shared = array[i];
    lock->writerCsExit();
  }
  //

  for (int i = 0; i < threadsNum; i++) {
    pthread_join(threadArray[i], NULL);
  }

  delete lock;
  delete a;

  free(threadArray);
  free(array);

  exit(EXIT_SUCCESS);
}
