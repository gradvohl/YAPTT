# Time to code
This section will illustrate how to pass parameters to the threads and get the return of a thread using the PThread API. First, we will describe a problem to motivate and contextualize the parameters passing. After that, we will delve into the code.

## Problem description and the strategy to solve it
We want to search for an element in an array with 40 integers in random order. Therefore, we will divide the array into four partitions and let each thread search sequentially in a partition assigned to it. 

If a thread finds the element, it will tell the others to stop searching and return the element's position. If a thread does not find the element in the partition, it will return ``-1``. Finally, the main thread will collect the results of all threads and show the element's position or the message "Element not found".

## Some information about the code
Although the example code is not that long, I divided it into different files. The goal is to facilitate the abstraction of concepts and, at the same time, to keep the code leaner. 

However, the reader need not worry because the ``makefile`` has all the instructions for compiling the code. So, all the user has to do is issue the ``make`` command. Besides, the ``make`` command will show the command lines for compiling each file separately and building the program in the end.

I divided the code into the following files:
- ``main.c`` with the main code, and the function ``searchElement`` responsible for instantiating the threads. 
- ``funcs.c`` and ``funcs.h`` with the code and respective header for auxiliary functions (create the arrays, search in arrays, and so on). 
- ``searchThreads.c`` and ``searchThreads.h`` with the code and respective header for the threads.

## Solution description
To solve the problem using multithreads, we will create threads that access their respective array partition. Besides, the threads shall receive the address of the array, two integers indicating the begin and the end of the partition, the element they will search for, and the address of a shared variable to tell when any thread finds the element.

### Structure to handle the thread input parameters
We define the following structure to handle the parameters we will pass to the thread. The definition of this structure is in the ``searchThreads.h`` file (line 19).
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

### Allocate the structure to handle the parameters and instantiate each thread
Now, let us turn our attention to the file ``main.c``, specifically to the function ``searchElement``, starting in line 26. After declaring the variables, we dynamically create an array of thread ids and enter in a loop to instantiate the threads.

In each iteration of that loop, we define the values for each field of the structure that will handle the parameters; allocate that structure dynamically; and instantiate a thread. Following is the code that performs the steps mentioned before.

```c
parameters *p;
register unsigned int begin, end;
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

The file ``funcs.c`` implements the ``parametersAllocation`` function, which dynamically allocates the structure to handle the parameters.

### Joining the threads
After instantiating the threads, they run and produce their results. Now, we need to block the main thread until the secondary threads finish. We call this "blocking until a thread finishes" as join.

Notice that we need another loop to join the main thread to each secondary thread. The code is following.

```c
for (i = 0; i < nthreads; i++)
{
  /* Wait for a specific thread to end. */
  pthread_join(threadIDs[i], &threadResult);

  /* Check if the element was found. */
  if (*((int *) threadResult) != -1)
  {
    fprintf(stdout, "Element found in position %d by thread %d.\n",
            *((int *) threadResult), i);
  }

  /* We don't need the variable 'threadResult' anymore.
   * So, let's free up the memory. 
   */
  free(threadResult);
}
```

In the previous code, we should highlight some details. Initially, let us observe the ``pthread_join`` primitive. The first parameter is the specific thread id that the main thread will join. Even if the threads finish in a different order than they were instantiated, there is no problem with other joins. But, it is the second parameter that worths mention.

The second parameter ``&threadResult`` is the address of a pointer, which will handle the address returned by the thread. If you look at line 34, you will see that I declared ``threadResult`` as ``void *``. Yet, I still passed the address of this variable to the ``pthread_join`` function. Giving the address of the variable is necessary because the ``pthread_join`` primitive will change the value handled by the ``threadResult`` variable.

It is worth watching how to check the value of the ``threadResult`` variable (in the if command in the previous code). Since ``threadResult`` is ``void *``, we need to cast the variable for ``(int *)`` first and, after that, check the address's content stored in ``threadResult`` variable. The following figure illustrates the procedure.

<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadCastingPointer.png?raw=true" align="center" width=376 />

Finally, since we do not need the address's contents pointed by the ``threadResult`` variable anymore, we can free up the memory and let the next call of ``pthread_join`` allocates the new ``threadResult`` variable.

### The thread function
Now, let us change our focus to the thread funcion in the ``searchThreads.c`` file. I want to highlight how can we copy the arguments we pass to the thread. The code for copy the arguments is the following.

```c
begin = ((parameters *) args)->begin;
end = ((parameters *) args)->end;
element = ((parameters *) args)->element;
array = ((parameters *) args)->array;
found = ((parameters *) args)->found;
```
Notice that, as stated [before](#Structure-to-handle-the-thread-input-parameters), we embed the parameters in a structure called ``parameters``. Also, we passed an address for that structure as an argument for this thread.

Therefore, to extract the parameters, we should first cast the ``args`` variable as type ``(parameters *)`` and then access the specific field of the structure with the operator ``->``. 

I usually declare local variables and copy the contents of structure fields into the variables. But, if you feel comfortable, you can use the structure fields directly.

We must highlight one specific detail for this problem. First, notice that the variable ``found`` is a pointer and stores an address. Intentionally, this address is the same for all threads because, once a thread changes this address's  contents, it will break the search loop in all other threads (as stated in the loop in line 62 in file ``searchThread.c``).

### Returning data from a thread
Remember that this thread should return the position of the found element or ``-1``. So, to return any data, we should allocate memory to handle the data, copy the data for the allocated memory and return the memory address. We performed these steps with the variable ``position`` within the ``searchThread`` function. Following are the commands we used.

```c
/** 
 * Let's allocate the position variable in memory. 
 */
 if ((position = (int *) malloc(sizeof(int))) == NULL)
 {
   fprintf(stderr, "Problems in memory allocation inside thread: %ld\n",
           pthread_self());
   exit(EXIT_FAILURE);
 }

 *position = -1;

/** 
 * Searching in the partition. 
 * If it is found, let's break the loop and warn the other threads
 * that this thread found the position of the element.
 */
 for (i = begin; i <= end && !(*found); i++)
   if (array[i] == element)
   {
     *position = i;
     *found = TRUE;
   }

/**
 * Return the position.  
 * If this thread didn't find the element, return *position == -1.
 */
 return ((void *) position);
}
```
Notice that we must cast it to ``(void *)`` to avoid compiler warnings when returning the ``position`` variable.

# Compiling and running
To compile this code, you can use the following command line:
```bash
make
```

It will compile all the files separately. Then, if everything is correct, it will build the program from the object files generated. The ``make`` command will show you the lines used in each step of the process.

To run the program, issue the following command. The program will present the array and ask you what element you want to search.
```bash
./searchThreads
```

# What's next?

Next, we will talk about [threads synchronization](../../syncThreads). Or, if you prefer, you can get back to the [main page](https://github.com/gradvohl/YAPTT).
