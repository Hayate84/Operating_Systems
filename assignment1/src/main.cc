#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "RWlock.h"

#define SMALLEST_ARRAY_SIZE 3000
#define FILENAMESIZE 30
#define NUMBERSIZE 20
#define PRETTY 20

struct Args {
  RWlock * lock;
  int shared;
  int arraySize;
};

// Print an array of ints with spacing based on PRETTY const
void printArray(int * array, int arraySize, FILE *fp) {
  int i;
  for (i = 1; i < arraySize + 1; ++i) {
    fprintf(fp, " %3d ", array[i - 1]);
    if (i % PRETTY == 0) {
      fprintf(fp, "\n  ");
    }
  }
  fprintf(fp, "\n");
}

void print_array_to_file(int * array, int arraySize, char * fileName, double running_average_time) {

  // Print the array to file
  FILE *fp;

  if (fp = fopen(fileName, "w")) {
    fprintf(fp, "Start thread with id number %li\n", pthread_self());
    fprintf(stdout, "Start thread with pid number %li\n", pthread_self());
    printArray(array, arraySize, fp);
    fprintf(fp, "End thread with pid number %li and running average time %5.2f\n", pthread_self());
    fprintf(stdout, "End thread with pid number %li and running average time %5.2f\n", pthread_self());
  } else {
    puts("Error: File can't be opened");
  }
  fclose(fp);
}

void * func_t(void * args) {
  Args * a = (Args *) args;
  int size = a->arraySize;

  int * array;
  if ((array = (int *) calloc(a->arraySize, sizeof(int))) == NULL) {
    perror("Not enough memory.");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    a->lock->readerCsEnter();
    array[i] = a->shared;
    a->lock->readerCsExit();
  }

  char fileName[FILENAMESIZE];
  strcpy(fileName, "logs/Thread_");

  char num[NUMBERSIZE];
  sprintf(num, "%li", pthread_self());

  strcat(fileName, num);

  print_array_to_file(array, a->arraySize, fileName, 3);
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

  char main[] = "main";
  print_array_to_file(array, a->arraySize, main, 3);
  for (int i = 0; i < threadsNum; i++) {
    pthread_join(threadArray[i], NULL);
  }

  delete lock;
  delete a;

  free(threadArray);
  free(array);

  exit(EXIT_SUCCESS);
}
