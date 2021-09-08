/**
 * Program to exemplify the use of semaphores with PThread
 * library.
 * The program uses multiple threads to search for the
 * largest element in an array of unordered non-repeating
 * integers.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#ifndef _SEARCHTHREADS
#  define _SEARCHTHREADS
#  include <limits.h>
#  include <semaphore.h>
#  define FALSE 0
#  define TRUE 1

typedef struct
{
  unsigned int position;
  int element;
} largestElementStrucuture;

typedef struct
{
  int *array;
  unsigned int begin;
  unsigned int end;
  sem_t *semaphore;
  largestElementStrucuture *largestElementField;
} parameters;

short exists(int elemento, int *vetor, int tamanho);
void *searchLargestElementThread(void *args);
parameters *parametersAllocation(unsigned int begin, unsigned int end,
                                 int *array, sem_t * semaphore,
                                 largestElementStrucuture *
                                 largestElementField);

largestElementStrucuture *largestElementStrucutureAllocation(unsigned int
                                                             position,
                                                             int element);
#endif
