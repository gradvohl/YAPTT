/**
 * A simple example to demonstrate the basics of PThreads API.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	5

/**
 * A thread that prints a message in the screen.
 */
void *printHello(void *args)
{
  pthread_t id;

  id = pthread_self();
  fprintf(stdout, "Hello world! My thread id: #%ld\n", id);

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  int t;

  for (t = 0; t < NUM_THREADS; t++)
  {
    fprintf(stdout, "Starting thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, printHello, NULL);

    if (rc)
    {
      fprintf(stderr, "ERROR: pthread_create() returns %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }

  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("Joining thread #%d\n", t);
    rc = pthread_join(threads[t], NULL);

    if (rc)
    {
      fprintf(stderr, "ERROR: pthread_join() returns %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }

  return 0;
}
