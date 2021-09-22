/**
 * A group of auxiliary functions for programs to exemplify
 * synchronization with semaphor and mutex.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "funcs.h"
#define FALSE 0
#define TRUE  1

/**
 * Checks if an element already exists in an array (disordered).
 * The search starts at position zero.
 * @param element Element to be searched in the array.
 * @param array Array where the element is searched.
 * @param size Array size.
 *
 * @return FALSE (0) if the element does not exist in the array.
 *         TRUE otherwise.
 */
short exists(int element, int *array, int size)
{
  register int i;

  if (size > 0)
    for (i = 0; i < size; i++)
      if (array[i] == element)
      {
        return TRUE;
      }

  return FALSE;
}

/**
 * Creates an array of random integers with a specific size.
 * @param size Array size.
 *
 * @return The address of the allocated array.
 */
int *createRandomArray(unsigned int size)
{
  register unsigned int i;
  int element;
  int *array;

  srand(time(NULL));

  if ((array = (int *) malloc(sizeof(int) * size)) == NULL)
  {
    fprintf(stderr, "There is an Error in the array memory allocation.\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < size; i++)
  {
    element = rand() % (size + 1);
    if (!exists(element, array, i))
      array[i] = element;
    else
      i--;
  }

  return array;
}

/**
 * Print the array in the screen.
 * @param array Array to be printed in the screen.
 * @param size Array size.
 */
void printArray(int *array, unsigned int size)
{
  register unsigned int i;

  fprintf(stdout, "Array: [");
  for (i = 0; i < size - 1; i++)
  {
    fprintf(stdout, "%d, ", array[i]);
  }

  fprintf(stdout, "%d]\n", array[i]);
}

/**
 * Allocates an array of thread identifiers in memory.
 *
 * @param size Size of the array.
 *
 * @return Memory address of the array.
 */
pthread_t *threadIDsAllocation(unsigned int size)
{
  pthread_t *threadsIDs = NULL;

  if (size > 0)
  {
    if ((threadsIDs = (pthread_t *) malloc(sizeof(pthread_t) * size)) == NULL)
    {
      fprintf(stderr, "Problems on allocating threads ids array in memory\n");
      exit(EXIT_FAILURE);
    }
  }

  return threadsIDs;
}
