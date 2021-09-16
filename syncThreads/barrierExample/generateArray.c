#include "generateArray.h"

void *generateAndCheck(void *args)
{
  register unsigned int i;
  register unsigned int begin, end;
  register unsigned int elseBegin, elseEnd;
  register unsigned int myID;
  int number;
  int *array;
  pthread_barrier_t *barrier;
  
  begin = ((parameters *) args)->begin;
  end = ((parameters *) args)->end;
  myID = ((parameters *) args)->myID;
  array = ((parameters *) args)->array;

  for (i=begin; i<=end; i++)
  {
    number = getNumber();
    if (!exists(number, begin, end))
    {
      array[i] = number;
      continue;  
    } 
    else
      i--;
  }

  
}
