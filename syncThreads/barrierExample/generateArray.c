#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "generateArray.h"
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

  for (i = begin; i <= end; i++)
  {
    do
    {
      number = rand()%LASTARRAYPOSITION;
    }
    while (exists(number, array, begin, end));

    array[i] = number;
  }

  // Synchronization point
  rc = pthread_barrier_wait(barrier);
  if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
  {
    fprintf(stderr, "Could not wait on barrier\n");
    exit(EXIT_FAILURE);
  }

  if (myID == 0)                /* If I am the first thread */
  {
    elseBegin = end + 1;
    elseEnd = LASTARRAYPOSITION;

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
