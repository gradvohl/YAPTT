/**
 * A collection of auxiliary functions for the program 
 * to exemplify the barrier synchronization method.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funcs.h"

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
short exists(int element, int *array, unsigned int begin, unsigned int end)
{
  register int i;

  for (i = begin; i <= end; i++)
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
int *createArray(unsigned int size)
{
  int *array;

  if ((array = (int *) malloc(sizeof(int) * size)) == NULL)
  {
    fprintf(stderr, "There is an Error in the array memory allocation.\n");
    exit(EXIT_FAILURE);
  }

  return array;
}

/**
 * Print the array in the screen, ten elements per line.
 * @param array Array to be printed in the screen.
 * @param size Array size.
 */
void printArray(int *array, unsigned int size)
{
  register unsigned int i;

  fprintf(stdout, "Array: [");
  for (i = 0; i < (size - 1); i++)
  {
    fprintf(stdout, "%d, ", array[i]);
    if (!((i + 1) % 10))
      fprintf(stdout, "\n%d:\t", i + 1);
  }

  fprintf(stdout, "%d]\n", array[i]);
}
