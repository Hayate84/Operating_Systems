#include <stdio.h>
#include <pthread.h>

#include "printFunctions.h"

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
  FILE *fp;

  if (fp = fopen(fileName, "w")) {
    fprintf(stdout, "Start thread with pid number %li\n", pthread_self());
    printArray(array, arraySize, fp);
    fprintf(stdout, "End thread with pid number %li and running average time %5.2f\n", pthread_self());
  } else {
    puts("Error: File can't be opened");
  }
  fclose(fp);
}
