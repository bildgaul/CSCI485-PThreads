// A modified version of the code from book's example threading program
// Uses mutex locks because I couldnt find anything specifically called a pthread lock

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t plock;
int NUM_INCS = 10000; // global non-constant so it can be accessed by increment_value

void *increment_value(void *value)
{
  pthread_mutex_lock(&plock);
  for (int i = 0; i < NUM_INCS; i++){
    (*(int*)value)++;
  }
  pthread_mutex_unlock(&plock);
  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  int numThreads = 4; // default
  if (argc == 2) { // in case only one argument is provided
    numThreads = atoi(argv[1]);
  }
  else if (argc >= 3){
    numThreads = atoi(argv[1]);
    NUM_INCS = atoi(argv[2]);
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
