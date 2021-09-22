/**
 * Program to exemplify the use of barriers in the 
 * PThread library.
 * The program creates two threads to fill an array with
 * 100 integers. Each thread will fill its array partition
 * with non repeated integers. After that, one thread will
 * indicate the position of duplicate elements in the 
 * array.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "generateAndCheck.h"
#include "funcs.h"
#define ARRAYSIZE 100
#define NTHREADS 2

int main(int argc, char *argv[])
{
  register unsigned short i;
  pthread_t threadIDs[NTHREADS];
  parameters param[NTHREADS];
  pthread_barrier_t barrier;
  int *array;

  srand(time(NULL));
  /**
   * Allocate the array in memory.
   */
  array = createArray(ARRAYSIZE);

  /**
   * Initialize the barrier variable.
   */
  if (pthread_barrier_init(&barrier, NULL, NTHREADS))
  {
    fprintf(stderr, "Cannot create a barrier\n");
    exit(EXIT_FAILURE);
  }

  /**
   * Set the parameters for each thread and 
   * create the threads.
   */
  for (i = 0; i < NTHREADS; i++)
  {
    param[i].myID = i;
    param[i].begin = i * (ARRAYSIZE / NTHREADS);
    param[i].end = ((i + 1) * (ARRAYSIZE / NTHREADS)) - 1;
    param[i].barrier = &barrier;
    param[i].array = array;

    if (pthread_create
        (&threadIDs[i], NULL, generateAndCheck, (void *) &param[i]))
    {
      fprintf(stderr, "Could not create thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }

  /**
   * Wait for threads to finish.
   */
  for (i = 0; i < NTHREADS; i++)
  {
    if (pthread_join(threadIDs[i], NULL))
    {
      fprintf(stderr, "Could not join thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }

  printArray(array, ARRAYSIZE);

  /**
   * Desallocate the array from memory.
   */
  free(array);

  /**
   * Destroy the barrier.
   */
  pthread_barrier_destroy(&barrier);

  return 0;
}
