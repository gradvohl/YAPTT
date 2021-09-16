#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAYSIZE 100
#define NTHREADS 2


int main(int argc, char *argv[])
{
  register unsigned short i;
  pthread_t threadIDs[NTHREADS];
  parameters param[NTHREADS];

  pthread_barrier_t barrier;

  if (pthread_barrier_init(&barrier, NULL, NTHREADS))
  {
    fprintf(stderr, "Cannot create a barrier\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < NTHREADS; i++)
  {
    if (pthread_create(&threadIDs[i], NULL, Thread, (void *) &param[i]))
    {
      fprintf(stderr, "Could not create thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < NTHREADS; i++)
  {
    if (pthread_join(threadIDs[i], NULL))
    {
      fprintf("Could not join thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }


  return 0;
}
