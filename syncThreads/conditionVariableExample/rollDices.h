#ifndef _THREADS_H
#define _THREADS_H
#include <pthread.h>

typedef struct {
  pthread_cond_t *cond;
  pthread_mutex_t *lock;
} parameters;

void *blockedThread(void *arg);
void *generateNumbers(void *arg);
#endif
