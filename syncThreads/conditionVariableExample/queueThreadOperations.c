#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queueThreadOperations.h"
#define FILLTHEQUEUE 5

void *fillQueue(void *args)
{
  register unsigned short i;
  pthread_mutex_t *mutex;
  pthread_mutex_t *mutexQueue;
  pthread_cond_t *count_threshold_cv;
  unsigned short thrdID;
  short number;

  mutex = ((parameters *) args)->mutex;
  mutexQueue = ((parameters *) args)->mutexQueue;
  count_threshold_cv = ((parameters *) args)->count_threshold_cv;
  thrdID = ((parameters *) args)->thrdID;

  for (i = 0; i < FILLTHEQUEUE; i++)
  {
    number = (numero() % 50);
    pthread_mutex_lock(mutex);
    /* 
     *     Check the value of count and signal waiting thread when condition is
     *         reached.  Note that this occurs while mutex is locked. 
     *             */
    if (isFull())
    {
      fprintf(stdout, "(Thrd: %d) The queue is full!\n", thrdID);
      pthread_cond_signal(count_threshold_cv);
      printf("Just sent signal.\n");
    }

      pthread_mutex_lock(mutexQueue);

      enqueue(number);
      fprintf(stdout, "(Thrd: %d) Add %d to the queue\n", thrdID, number);

    pthread_mutex_unlock(mutexQueue);


    pthread_mutex_unlock(mutex);
  }

  pthread_exit(NULL);
}

void *emptyQueue(void *args)
{
  pthread_mutex_t *mutex;
  pthread_cond_t *count_threshold_cv;
  short thrdID = ((parameters *) args)->thrdID;

  mutex = ((parameters *) args)->mutex;
  count_threshold_cv = ((parameters *) args)->count_threshold_cv;
  
  fprintf(stdout, "Starting emptyQueue thread (Thrd: %d) \n", thrdID);

  /*
   *   Lock mutex and wait for signal.  Note that the pthread_cond_wait routine
   *     will automatically and atomically unlock mutex while it waits. 
   *       Also, note that if COUNT_LIMIT is reached before this routine is run by
   *         the waiting thread, the loop will be skipped to prevent pthread_cond_wait
   *           from never returning.
   *             */
  pthread_mutex_lock(mutex);
  while (!isFull() || isEmpty())
  {
    fprintf(stdout, "emptyQueue Going into wait...\n");
    pthread_cond_wait(count_threshold_cv, mutex);
    fprintf(stdout, "emptyQueue thread condition signal received.\n");
  }

  fprintf(stdout, "Clearing the queue: [ ");
  while (!isEmpty())
  {
    fprintf(stdout, "%d ", dequeue());
  }

  fprintf(stdout, "]\n");

  pthread_mutex_unlock(mutex);

  pthread_exit(NULL);
}

parameters *parametersAllocation(pthread_mutex_t * mutex, pthread_mutex_t *mutexQueue,
                                 pthread_cond_t * count_threshold_cv,
                                 unsigned short thrdID)
{
  parameters *p;

  if ((p = (parameters *) malloc(sizeof(parameters))) == NULL)
  {
    fprintf(stderr, "Problems in memory allocation for parameters.\n");
    exit(EXIT_FAILURE);
  }

  p->mutex = mutex;
  p->mutexQueue = mutexQueue;
  p->count_threshold_cv = count_threshold_cv;
  p->thrdID = thrdID;

  return p;
}
