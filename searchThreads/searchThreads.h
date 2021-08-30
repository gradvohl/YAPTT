/**
 * Functions' headers to support the program to exemplify the 
 * use of the PThread library.
 * The program creates multiple threads to search for an
 * element in an unordered array of non-repeating elements.
 *
 * Author: Andre Leon S. Gradvohl, Dr.
 */
#ifndef _SEARCHTHREADS
#  define _SEARCHTHREADS

#  define FALSE 0
#  define TRUE 1

typedef struct
{
  int *array;
  unsigned int begin;
  unsigned int end;
  int element;
  short *found;
} parameters;

void *searchThread(void *args);
parameters *parametersAllocation(unsigned int begin, unsigned int end,
                                 int element, int *array, short *found);
#endif
