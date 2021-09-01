# Time to code
This section will illustrate how to pass parameters to the threads and how to get the return of a thread using the PThread API. First, we will describe a problem to contextualize and motivate the parameters passing. After that, we will delve into the code.

## Problem description
We want to search for an element in an array with 40 integers in random order. Therefore, we will divide the array into four partitions for that task and let each thread search sequentially in its partition. 

If a thread finds the element, it will tell the others to stop searching and return the element's position. If a thread does not find the element, it will return ``-1``. Finally, the main thread will collect the results of all threads and show the element's position or the message "Element not found".

## Some information about the code
Although the example code is not that long, I made sure to separate it into different files. The goal is to facilitate the abstraction of concepts and, at the same time, to keep the code leaner. 

However, the reader need not worry because the ``makefile`` has all the instructions for compiling the code. All the user has to do is issue the ``make`` command.

I divided the code into the following files:
- ``main.c`` with the main code, and the function ``searchElement`` responsible for instantiating the threads. 
- ``funcs.c`` and ``funcs.h`` with the code and respective header for auxiliary functions (create the arrays, search in arrays, and so on). 
- ``searchThreads.c`` and ``searchThreads.h`` with the code and respective header for the threads.

## Solution description
To solve the problem using multithreads, we will create threads that access their respective array partition. Besides, the threads shall receive the element they will search for, two integers indicating the begin and the end of the partition, and the address of a shared variable to tell when any thread finds the element.

### Structure to handle the thread input parameters

We define the following structure to handle the parameters we will pass to the thread. The definition of this structure is in the ``searchThreads.h`` file (line 15).
```c
typedef struct
{
  int *array;         // Address of the shared array between threads
  unsigned int begin; // Begin of the partition
  unsigned int end;   // End of the partition
  int element;        // Element to search for.
  short *found;       // Address of a a shared variable to tell when the element is found.
} parameters;
```

### Allocate the structure to handle the parameters and instantiate the thread
Now, let us turn our attention to the file ``main.c``, specifically to the function ``searchElement``, starting in line 26. After declaring the variables, we dynamically create an array of thread ids and enter in a loop to instantiate the threads.

In each iteration of that loop, we define the values for each field of the structure that will handle the parameters; we allocate that structure dynamically; and instantiate the thread. Following is the code that performs the steps mentioned before.

```c
register unsigned int begin, end;
parameters *p;
short found = FALSE;
...
for (i = 0; i < nthreads; i++)
{
  /* Define the initial position of the partition. */
  begin = i * (size / nthreads);

  /* Define the final position of the partition. */
  end = (i + 1) * (size / nthreads);

  /* Allocate the parameters for this specific thread. */
  p = parametersAllocation(begin, end, element, array, &found);

  /* Create the specific thread. */
  if (pthread_create(&threadIDs[i], NULL, searchThread, p))
  {
    fprintf(stderr, "Problems in thread %d creation\n", i);
    exit(EXIT_FAILURE);
  }
}
```

The file ``funcs.c`` implements the ``parametersAllocation`` function.
