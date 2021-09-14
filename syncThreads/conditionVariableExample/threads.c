#include <stdio.h>
#include <pthread.h>
#include "threads.h"

void *blockedThread(void *args)
{
 
  pthread_cond_t *cond;
  pthread_mutex_t *lock;

  cond = ((parameters *) args)->cond;
  lock = ((parameters *) args)->lock;
 
 // acquire a lock
 pthread_mutex_lock(lock);
 printf("Waiting on condition variable cond\n");
 pthread_cond_wait(cond, lock);
 // release lock
 pthread_mutex_unlock(lock);
 
 printf("Returning thread\n");

 pthread_exit(NULL);
}

void *generateNumbers(void *arg)
{
  int i;
  pthread_cond_t *cond;

  cond = ((pthread_cond_t *) arg);

  do {
     i = rand()%8;
     printf("i: %d\n", i);
  } while ( i != 7);

  printf("Get a 7\n");
  pthread_cond_signal(cond);
  pthread_exit(NULL); 
}
