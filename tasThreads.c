// A modified version of the code from book's example threading program
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int numIncs = 10000; // global non-constant so it can be accessed by increment_value
bool lock = false; // also global non-constant so it can be set before increment_value is called
// https://en.wikipedia.org/wiki/Test-and-set, could not find a tas lock to include

int check_tas(bool *lock)
{
  bool old = *lock;
  *lock = true;
  return old;
}

void *increment_value(void *value)
{
  while (check_tas(&lock));
  for (int i = 0; i < numIncs; i++){
    (*(int*)value)++;
  }
  lock = false;
  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  int numThreads = 4; // default
  if (argc == 3) {
    if (strcmp(argv[1], "-x") == 0)
      numThreads = atoi(argv[2]);
    else if (strcmp(argv[1], "-y") == 0)
      numIncs = atoi(argv[2]);
  }
  else if (argc == 5) {
    if (strcmp(argv[1], "-x") == 0 && strcmp(argv[3], "-y\
") == 0) {
      numThreads = atoi(argv[2]);
      numIncs = atoi(argv[4]);
    }
    else if (strcmp(argv[1], "-y") == 0 && strcmp(argv[3]\
, "-x") == 0) {
      numIncs = atoi(argv[2]);
      numThreads = atoi(argv[4]);
    }
  }
  
  // The main program creates 10 threads and then exits.
  pthread_t threads[numThreads];
  int status;

  int value = 0;
  int *valueptr = &value;
  for (int i = 0; i < numThreads; i++){
    status = pthread_create(&threads[i], NULL, increment_value, valueptr);
    pthread_join(threads[i], NULL);
    if (status != 0){
      printf("Oops, pthread_create returned error code %d\n", status);
      exit(-1);
    }
  }
  printf("Value: %d\n", value);
  exit(0);
}
