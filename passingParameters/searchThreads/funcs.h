/**
 * Header to auxiliary functions to support a program 
 * to exemplify the use of the PThread library.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#ifndef _AUXFUNCS
#  define _AUXFUNCS
short exists(int element, int *array, int size);
int *createRandomArray(unsigned int tamanho);
void printArray(int *vetor, unsigned int tamanho);
pthread_t *threadIDsAllocation(unsigned int quantity);
#endif
