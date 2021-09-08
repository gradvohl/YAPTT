/**
 * Program to exemplify the use of semaphores with PThread 
 * library.
 * The program uses multiple threads to search for the 
 * largest element in an array of unordered non-repeating 
 * integers.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "funcs.h"
#include "searchThreadsSemaphore.h"
#define SIZE 40
#define NTHREADS 4

/**
 * Procedure to get the largest element in an array. 
 * The procedure will divide the array into threads and 
 * each thread will get the largest element in its partition.
 * After that this procedure will show the largest element
 * among the elements each thread returned.
 *
 * @param array Array where the procedure will search for the element.
 * @param size Array size
 * @param nthreads Number of threads to search for the element.
 *
 * @return An address of the structure with the largest element and
 *         its position in the array.
 */
void largestElement(int *array, unsigned int size, unsigned int nthreads)
{
  unsigned int i;
  parameters *p;
  register unsigned int begin, end;
  sem_t semaphore;
  largestElementStrucuture largestElementField;
  pthread_t *threadIDs;

  /**
   * Allocate an array of thread ids.
   */
  threadIDs = threadIDsAllocation(nthreads);

  /**
   * Initialize the semaphore.
   */
  sem_init(&semaphore, 0, 1);

  /**
   * Initialize the largestElementStrucuture.
   */
  largestElementField.element = INT_MIN;
  largestElementField.position = 0;
  /**
   * Create the numner of threads specified in 
   * the variable 'nthreads'.
   */
  for (i = 0; i < nthreads; i++)
  {
    /* Define the initial position of the partition. */
    begin = i * (size / nthreads);

    /* Define the final position of the partition. */
    end = (i + 1) * (size / nthreads);

    /* Allocate the parameters for this specific thread. */
    p = parametersAllocation(begin, end, array,
                             &semaphore, &largestElementField);

    /* Create the specific thread. */
    if (pthread_create(&threadIDs[i], NULL, searchLargestElementThread, p))
    {
      fprintf(stderr, "Problems in thread %d creation\n", i);
      exit(EXIT_FAILURE);
    }
  }

  /**
   * Join the main thread with each of the threads created.
   */
  for (i = 0; i < nthreads; i++)
  {
    /* Wait for a specific thread to end. */
    pthread_join(threadIDs[i], NULL);
  }

  /**
   * We don't need the semaphore anymore. 
   * So, we desallocate it.
   */ 
  sem_destroy(&semaphore);

  /**
   * Print the largest element.
   */ 
  fprintf(stdout, "The largest element (%d) is in position %d\n",
          largestElementField.element, largestElementField.position);
}

int main(int argc, char *argv[])
{
  int *array = NULL;

  srand(time(NULL));

  array = createRandomArray(SIZE);

  printArray(array, SIZE);

  largestElement(array, SIZE, NTHREADS);

  free(array);

  return 0;
}
