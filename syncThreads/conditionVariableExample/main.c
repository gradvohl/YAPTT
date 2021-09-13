#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queueThreadOperations.h"

int main(int argc, char *argv[])
{
  register int i;
  pthread_t threadIDs[3];
  pthread_mutex_t mutex;
  pthread_mutex_t mutexQueue;
  pthread_cond_t count_threshold_cv;
  parameters *param[3];

  createQueue(10);

  /* Initialize mutex and condition variable objects */
  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&mutexQueue, NULL);
  pthread_cond_init(&count_threshold_cv, NULL);

  for (i = 0; i < 3; i++)
  {
    param[i] =
      parametersAllocation(&mutex, &mutexQueue, &count_threshold_cv, i);
  }

  pthread_create(&threadIDs[0], NULL, emptyQueue, param[0]);
  pthread_create(&threadIDs[1], NULL, fillQueue, param[1]);
  pthread_create(&threadIDs[2], NULL, fillQueue, param[2]);

  for (i = 0; i < 3; i++)
  {
    pthread_join(threadIDs[i], NULL);
    free(param[i]);
  }

  /* Clean up and exit */
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&count_threshold_cv);

  return 0;
}
