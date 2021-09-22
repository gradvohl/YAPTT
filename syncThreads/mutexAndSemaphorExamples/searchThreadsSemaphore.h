/**
 * Header for the program to exemplify the use of semaphores
 * with PThread library. It includes the definitions of the
 * structures to handle the parameters.
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
} highestElementStrucuture;

typedef struct
{
  int *array;
  unsigned int begin;
  unsigned int end;
  sem_t *semaphore;
  highestElementStrucuture *highestElementField;
} parameters;

short exists(int elemento, int *vetor, int tamanho);
void *searchhighestElementThread(void *args);
parameters *parametersAllocation(unsigned int begin, unsigned int end,
                                 int *array, sem_t * semaphore,
                                 highestElementStrucuture *
                                 highestElementField);

highestElementStrucuture *highestElementStrucutureAllocation(unsigned int
                                                             position,
                                                             int element);
#endif
