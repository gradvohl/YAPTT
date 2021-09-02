/**
 * Functions to support the program to exemplify the use 
 * of the PThread library.
 * The program creates multiple threads to search for an
 * element in an unordered array of non-repeating elements.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "searchThreads.h"

/**
 * Thread to search for an element in an array partition.
 *
 * @param args Arguments for the thread.
 *
 * @return The address of a memory position that handles the
 *         position of the element in the array or -1 if it
 *         was not found.
 */
void *searchThread(void *args)
{
  register unsigned int begin, end, i;
  int element;
  int *array;
  int *position;
  short *found;

  /**
   * Copy the parameters in 'args' for local variables.
   */
  begin = ((parameters *) args)->begin;
  end = ((parameters *) args)->end;
  element = ((parameters *) args)->element;
  array = ((parameters *) args)->array;
  found = ((parameters *) args)->found;

  /**
   * We don't need 'args' anymore. So, let's free up the memory.
   */
  free(args);

  /** 
   * Let's allocate the position variable in memory. 
   */
  if ((position = (int *) malloc(sizeof(int))) == NULL)
  {
    fprintf(stderr, "Problems in memory allocation inside thread: %ld\n",
            pthread_self());
    exit(EXIT_FAILURE);
  }

  *position = -1;

  /** 
   * Searching in the partition. 
   * If it is found, let's break the loop and warn the other threads
   * that this thread found the position of the element.
   */
  for (i = begin; i <= end && !(*found); i++)
    if (array[i] == element)
    {
      *position = i;
      *found = TRUE;
    }

  /**
   * Return the position.  
   * If this thread didn't find the element, 
   * return *position == -1.
   */
  return ((void *) position);
}

/**
 * Function for allocating a structure to handle the parameters 
 * for the thread. The function also handles errors in memory 
 * allocation.
 *
 * @param begin Begin of the partition.
 * @param end End of the partition.
 * @param element Element to be searched for in the array.
 * @param array Array Where the thread will search.
 * @param found A flag to indicate if the element was found.
 *
 * @return The address of the allocated structure.
 */
parameters *parametersAllocation(unsigned int begin, unsigned int end,
                                 int element, int *array, short *found)
{
  parameters *p;

  if ((p = (parameters *) malloc(sizeof(parameters))) == NULL)
  {
    fprintf(stderr, "Problems in memory allocation for parameters.\n");
    exit(EXIT_FAILURE);
  }

  p->begin = begin;
  p->end = end;
  p->element = element;
  p->array = array;
  p->found = found;

  return p;
}
