/**
 * Program to exemplify the use of semaphores with PThread
 * library.
 * The program uses multiple threads to search for the
 * highest element in an array of unordered non-repeating
 * integers.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#ifndef _SEARCHTHREADSMUTEX
#  define _SEARCHTHREADSMUTEX
#  include <limits.h>
#  include <pthread.h>
#  define FALSE 0
#  define TRUE 1

typedef struct
{
  unsigned int position;
  int element;
} highestElementStrucuture;

typedef struct
{
  int *array;
  unsigned int begin;
  unsigned int end;
  pthread_mutex_t *mutex;
  highestElementStrucuture *highestElementField;
} parameters;

short exists(int elemento, int *vetor, int tamanho);
void *searchhighestElementThread(void *args);
parameters *parametersAllocation(unsigned int begin, unsigned int end,
                                 int *array, pthread_mutex_t* mutex,
                                 highestElementStrucuture *
                                 highestElementField);

highestElementStrucuture *highestElementStrucutureAllocation(unsigned int
                                                             position,
                                                             int element);
#endif
