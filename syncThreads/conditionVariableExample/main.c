/**
 * Program to exemplify the use of condition variables 
 * with PThread library.
 * The program creates two threads and one of them 
 * starts blocked. The other generates numbers randomly
 * and, when this number is 7, it unblocks the first
 * thread.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "rollDice.h"

int main(int argc, char *argv[])
{
  pthread_t threadIDs[2];
  parameters param;
  pthread_cond_t cond;
  pthread_mutex_t lock;

 /**
  * Initializing the condition variable and the mutex.
  */
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&lock, NULL);

 /**
  * Fill the structure with the variables addresses.
  */
  param.cond = &cond;
  param.lock = &lock;

 /**
  * Setting the seed for a new sequence of pseudo-random integers.
  */
  srand(time(NULL));

 /**
  * Creating the first thread. 
  */
  pthread_create(&threadIDs[0], NULL, blockedThread, (void *) &param);

  /**
   * Take a second to guarantee that the first thread is blocked.
   */     
  sleep(1);

  /**
   * Creating the second thread.
   * Notice that this thread only needs the condition variable address.
   */
  pthread_create(&threadIDs[1], NULL, generateNumbers, (void *) &cond);

 /**
  * Joining threads.
  */
  pthread_join(threadIDs[0], NULL);
  pthread_join(threadIDs[1], NULL);

 /**
  * Destroying the mutex and the condition variable.
  */
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);

  return 0;
}
