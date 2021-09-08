# Semaphores and mutexes example
This section shows how to implement synchronization, one of them using semaphores and the other using mutexes. As mention before, semaphores and mutexes are very alike. The difference is that semaphores can handle values greater or equal to zero, while mutexes handle two states: lock and unlock.

## Problem description and the strategy to solve it
The problem is to search for the maximum value in an array of 40 non-ordered random integers. Therefore, we will divide the array into four partitions and let each thread calculates the largest value in the partition assigned to it. 

In the end, each thread compares its largest integer found with a shared variable (a structure) that handles the largest integer found so far and its position in the array. After all the threads finish, the main thread will print the largest integer and its position in the array.

As the reader may suspect, that shared variable is a **critical region**. Therefore, we should create a **mutual exclusion zone** around this critical region to ensure that only one thread at a time will query and, if necessary, change the value of this variable.

First, we will present the solution using [semaphores](#Semaphore-solution). After, we will present the solution using [mutexes](#Mutex-solution). The programs are very similar. The main difference is in the commands used to establish the mutual exclusion zone.

## Semaphore solution
As we did in previous examples, we divided the code into different files to facilitate some abstractions. Therefore, we will focus on the details of semaphores and synchronization. I documented the rest of the code, so it will be easy to understand.

To use semaphores, we must also include the ``semaphore.h`` header that will give us the primitives and data types for using them.

### Semaphore declaration, initialization, and destroy
Now, let us look at the ``main.c`` file that contains the function ``largestElement`` (in line 33), which is responsible for instantiating the threads. In that function, in line 38, we declared the ``sem_t semaphore`` variable, which we will use to synchronize the threads.

After the declaration, in line 50, we initialized the ``semaphore`` variable using the ``sem_init`` primitive. That primitive receives three parameters: the semaphore address, a flag to indicate if the semaphore is shared between threads (0) or if it is shared among processes (non zero), and the initial value (greater than or equal to zero). 

After initializing the semaphore, we can use it to block or unblock other threads, as we will describe later. Then, when we do not need the semaphore anymore, we can destroy it with the command ``sem_destroy``, as we did in line 94. 

### Structure to handle the parameters
For the thread to work, we will pass various parameters embedded in a structure defined in file ``searchThreads.h`` and replicated as follows.

```c
typedef struct
{
  unsigned int position;
  int element;
} largestElementStrucuture;

typedef struct
{
  int *array;
  unsigned int begin;
  unsigned int end;
  sem_t *semaphore;
  largestElementStrucuture *largestElementField;
} parameters;
```

Notice that the ``parameters`` structure has the following fields:
- ``array`` to handle the address of the array with the integers.
- ``begin`` and  ``end`` with the first and last positions of the array (partition) the thread will work on.
- ``semaphore`` to store the address of the semaphore shared between threads.
- ``largestElementField`` to store the address of a structure to handle the largest element and its position.

### Defining the mutual exclusion zone within the thread code
Now, let us focus on the thread code in file ``searchThreads.c``, within the function ``searchLargestElementThread`` (in line 25). We first declare all the local variables to handle the parameters passed to the thread, including the semaphore and the structure to handle the largest element and its position.

After copying the parameters to local variables, the thread searches for the largest element in its partition. Next, we use the command ``sem_wait(semaphore);`` to block access to the critical region (i. e., the ``largestElementField`` variable).

Notice that if the address pointed by the ``semaphore`` variable has a value greater than zero, the ``sem_wait`` primitive will decrement that value. Otherwise, if that value is zero, the thread that called the ``sem_wait`` primitive is blocked.

Therefore, if a thread passes through the ``sem_wait`` primitive, it can safely handle and update the ``largestElementField`` variable. Besides, when leaving the critical region, the thread must call the ``sem_post`` primitive to increment (and unlock other blocked threads) the address pointed by the ``semaphore`` variable.

I replicate the code as follows.

```c
sem_wait(semaphore);
if (element > largestElementField->element)
{
  largestElementField->element = element;
  largestElementField->position = position;
}
sem_post(semaphore);
```

### Compiling and running the code
To compile the code, you can issue the ``make`` command. To run the program, you can issue the command ``./searchThreads``.
