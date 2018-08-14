#include <stdio.h>
#include <stdlib.h>

#include "Init.h"

#define SMALLEST_ARRAY_SIZE 3000

Init::Init(int argc, char **argv) {

  // Invalid number of arguments
  if (argc != 3) {
    fprintf(stderr, "Error: Invalid number or arguments.\n");
    fprintf(stderr, " Please run with two. M > 3000 the size of the array");
    fprintf(stderr, " and N > 0 number of processes to be executed.\n");
    exit(EXIT_FAILURE);
  }

  // M the size of the array
  arraySize = atoi(argv[1]);

  // Invalid array size
  if (arraySize < SMALLEST_ARRAY_SIZE) {
    fprintf(stderr, "Error: Invalid array size.\n");
    fprintf(stderr, " Array size M must be > %d.\n", SMALLEST_ARRAY_SIZE);
    exit(EXIT_FAILURE);
  }

  // Number of consumer programs
  threadsNum = atoi(argv[2]);
  if (threadsNum < 1) {
    fprintf(stderr, "Error: Invalid number of threads.\n");
    fprintf(stderr, "Number of threads N must be > 0.\n");
    exit(EXIT_FAILURE);
  }
}
