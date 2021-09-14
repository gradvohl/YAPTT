/**
 * Program to ilustrate the cond
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threads.h"

int main(int argc, char *argv[])
{
 pthread_t threadIDs[2];
 parameters param;
 pthread_cond_t cond;
 pthread_mutex_t lock;

 pthread_cond_init(&cond, NULL);
 pthread_mutex_init(&lock, NULL);

 param.cond = &cond;
 param.lock = &lock;

 srand(time(NULL));

 pthread_create(&threadIDs[0], NULL, blockedThread, (void *) &param);
 pthread_create(&threadIDs[1], NULL, generateNumbers, (void *) &cond);
 
 pthread_join(threadIDs[0], NULL);
 pthread_join(threadIDs[1], NULL);

 pthread_cond_destroy(&cond);
 pthread_mutex_destroy(&lock);

 return 0;
}

