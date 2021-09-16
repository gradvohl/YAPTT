#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "generateArray.h"
#include "funcs.h"
#define ARRAYSIZE 100
#define NTHREADS 2


int main(int argc, char *argv[])
{
  register unsigned short i;
  pthread_t threadIDs[NTHREADS];
  parameters param[NTHREADS];
  int *array;

  array = createArray(ARRAYSIZE);
  
  pthread_barrier_t barrier;

  srand(time(NULL));

  if (pthread_barrier_init(&barrier, NULL, NTHREADS))
  {
    fprintf(stderr, "Cannot create a barrier\n");
    exit(EXIT_FAILURE);
  }

  
  param[0].barrier = param[1].barrier = &barrier;
  param[0].array = param[1].array = array;


  for (i = 0; i < NTHREADS; i++)
  {
    param[i].myID = i;
    param[i].begin = i*(ARRAYSIZE/NTHREADS);
    param[i].end = ((i+1)*(ARRAYSIZE/NTHREADS)) - 1;
    param[i].barrier = &barrier;
    param[i].array = array;
	
    if (pthread_create
        (&threadIDs[i], NULL, generateAndCheck, (void *) &param[i]))
    {
      fprintf(stderr, "Could not create thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < NTHREADS; i++)
  {
    if (pthread_join(threadIDs[i], NULL))
    {
      fprintf(stderr, "Could not join thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }

  printArray(array, ARRAYSIZE);

  free(array);

  return 0;
}
