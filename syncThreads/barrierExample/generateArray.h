#ifndef _GENERATEANDCHECK
#  define _GENERATEANDCHECK
#  include <pthread.h>

typedef struct
{
  int *array;
  unsigned int begin;
  unsigned int end;
  unsigned short myID;
  pthread_barrier_t *barrier;
} parameters;

void *generateAndCheck(void *args);
#endif
