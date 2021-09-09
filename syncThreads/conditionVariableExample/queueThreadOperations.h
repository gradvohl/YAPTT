#ifndef _QUEUETHREADOPERATIONS
#  define _QUEUETHREADOPERATIONS
#  include <pthread.h>

typedef struct
{
  pthread_mutex_t *mutex;
  pthread_mutex_t *mutexQueue;
  pthread_cond_t *count_threshold_cv;
  unsigned short thrdID;
} parameters;

parameters *parametersAllocation(pthread_mutex_t * mutex, pthread_mutex_t *mutexQueue,
                                 pthread_cond_t * count_threshold_cv,
                                 unsigned short thrdID);
void *fillQueue(void *args);
void *emptyQueue(void *args);
#endif
