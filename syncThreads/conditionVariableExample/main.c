#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queueThreadOperations.h"

int main(int argc, char *argv[])
{
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

  param[0] = parametersAllocation(&mutex, &mutexQueue, &count_threshold_cv, 0);
  param[1] = parametersAllocation(&mutex, &mutexQueue, &count_threshold_cv, 1);
  param[2] = parametersAllocation(&mutex, &mutexQueue, &count_threshold_cv, 2);

  pthread_create(&threadIDs[0], NULL, emptyQueue, param[0]);
  pthread_create(&threadIDs[1], NULL, fillQueue, param[1]);
  pthread_create(&threadIDs[2], NULL, fillQueue, param[2]);

  pthread_join(threadIDs[0], NULL);
  pthread_join(threadIDs[1], NULL);
  pthread_join(threadIDs[2], NULL);


  /* Clean up and exit */
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&count_threshold_cv);
  free(param[0]);
  free(param[1]);
  free(param[2]);

  return 0;
}
