/**
 * Program to exemplify the use of the PThread library.
 * The program creates multiple threads to search for an 
 * element in an unordered array of non-repeating elements.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funcs.h"
#include "searchThreads.h"
#define SIZE 40
#define NTHREADS 4

/**
 * Procedure to search elements in an array. The procedure will
 * divide the array into threads and each thread will search in
 * its partition.
 *
 * @param element Element to be searched in the array.
 * @param array Array where the procedure will search for the element.
 * @param size Array size
 * @param nthreads Number of threads to search for the element.
 */
void searchElement(int element, int *array, unsigned int size,
                   unsigned int nthreads)
{
  unsigned int i;
  register unsigned int begin, end;
  parameters *p;
  short found = FALSE;
  void *threadResult;
  pthread_t *threadIDs;

  /**
   * Allocate an array of thread ids.
   */
  threadIDs = threadIDsAllocation(nthreads);

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
    p = parametersAllocation(begin, end, element, array, &found);

    /* Create the specific thread. */
    if (pthread_create(&threadIDs[i], NULL, searchThread, p))
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
    pthread_join(threadIDs[i], &threadResult);

    /* Check if the element was found. */
    if (*((int *) threadResult) != -1)
    {
      fprintf(stdout, "Element found in position %d by thread %d.\n",
              *((int *) threadResult), i);
    }

    /* We don't need the variable 'threadResult' anymore.
     * So, let's free up the memory. 
     */
    free(threadResult);
  }

  if (!found)
    fprintf(stderr, "Element not found\n");
}

int main(int argc, char *argv[])
{
  int element = 0;
  int *array = NULL;

  srand(time(NULL));

  array = createRandomArray(SIZE);

  printArray(array, SIZE);

  printf("Element to search in the array:");
  scanf("%d", &element);

  searchElement(element, array, SIZE, NTHREADS);

  free(array);

  return 0;
}
