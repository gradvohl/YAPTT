/**
 * Program to exemplify the use of semaphores with PThread
 * library.
 * The program uses multiple threads to search for the
 * highest element in an array of unordered non-repeating
 * integers.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "searchThreadsSemaphore.h"

/**
 * Thread to search for an element in an array partition.
 *
 * @param args Arguments for the thread.
 *
 * @return The address of a memory position that handles the
 *         position of the element in the array or -1 if it
 *         was not found.
 */
void *searchhighestElementThread(void *args)
{
  register unsigned int begin, end, i;
  unsigned int position;
  int element = INT_MIN;
  int *array;
  sem_t *semaphore;
  highestElementStrucuture *highestElementField;

  /**
   * Copy the parameters in 'args' for local variables.
   */
  position = begin = ((parameters *) args)->begin;
  end = ((parameters *) args)->end;
  array = ((parameters *) args)->array;
  semaphore = ((parameters *) args)->semaphore;
  highestElementField = ((parameters *) args)->highestElementField;


  /**
   * We don't need 'args' anymore. So, let's free up the memory.
   */
  free(args);

  /** 
   * Searching in the partition. 
   * If it is found, let's break the loop and warn the other threads
   * that this thread found the position of the element.
   */
  for (i = begin; i <= end; i++)
    if (array[i] > element)
    {
      element = array[i];
      position = i;
    }

  /**
   * Block the access to the shared variable, and 
   * update it if necessary. 
   */
  sem_wait(semaphore);
  if (element > highestElementField->element)
  {
    highestElementField->element = element;
    highestElementField->position = position;
  }
  sem_post(semaphore);

  pthread_exit(NULL);
}

/**
 * Function for allocating a structure to handle the parameters 
 * for the thread. The function also handles errors in memory 
 * allocation.
 *
 * @param begin Begin of the partition.
 * @param end End of the partition.
 * @param array Array Where the thread will search.
 *
 * @return The address of the allocated structure.
 */
parameters *parametersAllocation(unsigned int begin, unsigned int end,
                                 int *array, sem_t * semaphore,
                                 highestElementStrucuture *
                                 highestElementField)
{
  parameters *p;

  if ((p = (parameters *) malloc(sizeof(parameters))) == NULL)
  {
    fprintf(stderr, "Problems in memory allocation for parameters.\n");
    exit(EXIT_FAILURE);
  }

  p->begin = begin;
  p->end = end;
  p->array = array;
  p->semaphore = semaphore;
  p->highestElementField = highestElementField;

  return p;
}
