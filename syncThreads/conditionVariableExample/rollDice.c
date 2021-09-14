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
#include <pthread.h>
#include "rollDice.h"

/**
 * This thread remains blocked until the other thread
 * gets the number 7 generated randomly.
 */ 
void *blockedThread(void *args)
{
  pthread_cond_t *cond;
  pthread_mutex_t *lock;

  /**
   * Copying the arguments passed as parameters
   * into local variables.
   */ 
  cond = ((parameters *) args)->cond;
  lock = ((parameters *) args)->lock;

  /**
   * Acquire a lock
   */  
  pthread_mutex_lock(lock);
 
  fprintf(stdout, "Waiting on a condition variable.\n");
  pthread_cond_wait(cond, lock);

  /**
   * Release the lock.
   */  
  pthread_mutex_unlock(lock);

  fprintf(stdout, "The other thread get a 7. I am out.\n");

  pthread_exit(NULL);
}

/**
 * This thread generates random integers. 
 * When a generated number is 7, it releases the other thread.
 */  
void *generateNumbers(void *arg)
{
  register unsigned int i;
  pthread_cond_t *cond;

  /**
   * Getting the address of the condition variable, passed as
   * an argument for this thread.
   */   
  cond = ((pthread_cond_t *) arg);

  /**
   * Generates random numbers until it founds number 7.
   */ 
  do
  {
    fprintf(stdout, "Number: %d\n", i = rand() % 8);
  } while (i != 7);

  fprintf(stdout, "I get a 7. Releasing the other thread!\n");
  pthread_cond_signal(cond);

  pthread_exit(NULL);
}
