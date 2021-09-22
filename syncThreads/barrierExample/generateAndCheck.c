/**
 * The implementation of a thread to generate the 
 * integers, add them to a partition, and check if
 * there are duplicate numbers between partitions.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "generateAndCheck.h"
#define LASTARRAYPOSITION 99

void *generateAndCheck(void *args)
{
  register unsigned int i, j;
  register unsigned int begin, end;
  register unsigned int elseBegin, elseEnd;
  register unsigned int myID;
  int rc;
  int number;
  int *array;
  pthread_barrier_t *barrier;

  begin = ((parameters *) args)->begin;
  end = ((parameters *) args)->end;
  myID = ((parameters *) args)->myID;
  array = ((parameters *) args)->array;
  barrier = ((parameters *) args)->barrier;

  /**
   * Generate an unique integer and 
   * add it to a partition.
   */
  for (i = begin; i <= end; i++)
  {
    do
    {
      number = rand() % (LASTARRAYPOSITION + 1);
    }
    while (exists(number, array, begin, end));

    array[i] = number;
  }

  /**
   *  Set the barrier.
   */
  rc = pthread_barrier_wait(barrier);

  /**
   * Check if the pthread_barrier_wait returns zero or
   * PTHREAD_BARRIER_SERIAL_THREAD. Both values indicate
   * that the threads reached the barrier. 
   * Other values indicate an error. 
   */
  if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
  {
    fprintf(stderr, "Could not wait on barrier\n");
    exit(EXIT_FAILURE);
  }

  /**
   *  If I am the first thread, 
   *  I will check for duplicates.
   */
  if (myID == 0)
  {
    /*Defining the begin and end of the other partition. */
    elseBegin = end + 1;
    elseEnd = LASTARRAYPOSITION;

    /* Looking for duplicates. */
    for (i = begin; i <= end; i++)
    {
      for (j = elseBegin; j <= elseEnd; j++)
        if (array[i] == array[j])
          fprintf(stdout, "Element: %d found in positions %d and %d\n",
                  array[i], i, j);
    }
  }

  pthread_exit(NULL);
}
