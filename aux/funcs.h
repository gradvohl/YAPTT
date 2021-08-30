#ifndef _AUXFUNCS
#  define _AUXFUNCS
   short existe(int elemento, int *vetor, int tamanho);
   int *createRandomArray(unsigned int tamanho);
   void printArray(int *vetor, unsigned int tamanho);
   pthread_t *threadIDsAllocation(unsigned int quantity);
#endif
