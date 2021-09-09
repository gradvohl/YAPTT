#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int *queue = NULL;
int start = 0;
int end = 0;
unsigned int queueSize = 0;
unsigned int quantElements = 0;

void enqueue(int element)
{
  if (queue == NULL)
  {
    fprintf(stderr, "Queue does not exists!\n");
    exit(EXIT_FAILURE);
  }

  if (isFull())
  {
    fprintf(stderr, "Queue is full!\n");
    exit(EXIT_FAILURE);
  }

  queue[end] = element;
  end = (end + 1) % queueSize;
  quantElements++;
  return;
}

int dequeue(void)
{
  register int elem;

  if (queue == NULL)
  {
    fprintf(stderr, "Queue does not exists!\n");
    exit(EXIT_FAILURE);
  }
  
  if (isEmpty())
  {
    fprintf(stderr, "Queue is empty!\n");
    exit(EXIT_FAILURE);
  }

  elem = queue[start];
  start = (start - 1) % queueSize;
  quantElements--;

  return elem;
}

short isFull()
{
  if (quantElements == queueSize)
    return 1;
  else
    return 0;
}

short isEmpty()
{
  return !quantElements;
}

int *createQueue(unsigned int size)
{
  if ((queue = (int *) malloc(sizeof(int) * size)) == NULL)
  {
    fprintf(stderr, "Error in creating queue!\n");
    exit(EXIT_FAILURE);
  }

  queueSize = size;
  quantElements = start = end = 0;

  return queue;
}

short numero()
{
  static int n = 0;
  return n++;
}
