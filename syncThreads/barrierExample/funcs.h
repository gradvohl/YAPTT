#ifndef _AUXFUNCS
#  define _AUXFUNCS
#define FALSE 0
#define TRUE  1
   short exists(int element, int *array, unsigned int begin, unsigned int end);
   int *createArray(unsigned int size);
   void printArray(int *vetor, unsigned int size);
   pthread_t *threadIDsAllocation(unsigned int quantity);
#endif
