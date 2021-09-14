# Condition variable example
This section shows how to implement synchronization using a Condition Variable (CV). Different from mutexes, which synchronize thread access to data, a condition variable is a way to signalize to other threads that a condition happend. Therefore, the thread who received that signal may unblock itself and perform other operations.

In PThreads library, a CV always works together with a mutex. It works this way because, when the CV receives a signal it unlocks its associated mutex.

A solution using condition variable will have the following pattern (considering two threads)
```c
/** Thread one **/
/**
 * Verify a condition and avoid other threads from
 * altering it.
 */
pthread_mutex_lock(&lock);
while ( Condition is false)
    pthread_cond_wait(&cond, &lock);

/** 
 * Now, the condition is true and 
 * the thread can do some stuff.
 */
do_stuff();
pthread_mutex_unlock(&lock);
```

```c
/** Thread two **/
/**
 * Get the into the mutual exclusion zone.
 */
pthread_mutex_lock(&lock);

/**
 * Do some stuff to change a condition.
 */
do_stuff_change_condition();

/** 
 * Signalize other thread that the condition occur.
 */
pthread_cond_signal(&cond);

/**
 * Leave the mutual exclusion zone.
 */
pthread_mutex_unlock (&lock)
```


## Problem description and the strategy to solve it
The problem is to search for the maximum value in an array of 40 non-ordered random integers. Therefore, we will divide the array into four partitions and let each thread calculates the largest value in the partition assigned to it. 

In the end, each thread compares its largest integer found with a shared variable (a structure) that handles the largest integer found so far and its position in the array. After all the threads finish, the main thread will print the largest integer and its position in the array.

As the reader may suspect, that shared variable is a **critical region**. Therefore, we should create a **mutual exclusion zone** around this critical region to ensure that only one thread at a time will query and, if necessary, change the value of this variable.

First, we will present the solution using a [mutex](#Mutex-solution). After, we will present the solution using a [semaphore](#Semaphore-solution). The programs are very similar. The main difference is in the commands used to establish the mutual exclusion zone.

## Mutex solution
As we did in previous examples, we divided the code into different files to facilitate some abstractions. Therefore, we will focus on the details of using a mutex for synchronization. I documented the rest of the code, so it will be easy to understand.

### Mutex declaration, initialization, and destroy

Now, let us look at the ``mainMutex.c`` file that contains the function largestElement (in line 32), which is responsible for instantiating the threads. In that function, in line 37, we declared the ``pthread_mutex_t mutex`` variable, which we will use to synchronize the threads.

After the declaration, in line 49, we initialized the ``mutex`` variable using the ``pthread_mutex_init`` primitive. That primitive receives two parameters: the mutex address and the attributes for the mutex (we use ``NULL`` to indicate the use of the default attributes).

After initializing the mutex, we can use it to block or unblock other threads, as we will describe later. Then, when we do not need the mutex anymore, we can destroy it with the command ``pthread_mutex_destroy``, as we did in line 93.

### Structure to handle the parameters

For the thread to work, we will pass various parameters embedded in a structure defined in file ``searchThreadsMutex.h`` and replicated as follows.

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
  pthread_mutex_t *mutex;
  largestElementStrucuture *largestElementField;
} parameters;

```
Notice that the parameters structure has the following fields:
- ``array`` to handle the address of the array with the integers.
- ``begin`` and end with the first and last positions of the array (partition) the thread will work on.
- ``mutex`` to store the address of the mutex shared between threads.
- ``largestElementField`` to store the address of a structure to handle the largest element and its position.

### Defining the mutual exclusion zone within the thread code

Now, let us focus on the thread code in file ``searchThreadsMutex.c``, within the function ``searchLargestElementThread`` (in line 24). We first declare all the local variables to handle the parameters passed to the thread, including the mutex and the structure to handle the largest element and its position.

After copying the parameters to local variables, the thread searches for the largest element in its partition. Next, we use the command ``pthread_mutex_lock(mutex)`` to block access to the critical region (i. e., the largestElementField variable).

Therefore, if a thread passes through the ``pthread_mutex_lock``primitive, it can safely handle and update the largestElementField variable. Besides, when leaving the critical region, the thread must call the ``pthread_mutex_unlock`` to unlock other blocked threads.

I replicate the code as follows.

```c
/**
 * Block the access to the shared variable, and 
 * update it if necessary. 
 */
pthread_mutex_lock(mutex);
if (element > largestElementField->element)
{
  largestElementField->element = element;
  largestElementField->position = position;
}
pthread_mutex_unlock(mutex);
```

### Compiling and running the mutex code

The instructions for compiling are in the ``makefileMutex`` file. Therefore, to compile the code, you can issue the following ``make`` command. 
```sh
make -f makefileMutex
```

To run the program, you can issue the command ``./searchThreadsMutex``.

Next, we will see the solution using semaphores. Again, the program structure is the same, and only the synchronization primitives are different.

## Semaphore solution
As we did in previous examples, we divided the code into different files to facilitate some abstractions. Therefore, we will focus on the details of semaphores and synchronization. I documented the rest of the code, so it will be easy to understand.

To use semaphores, we must also include the ``semaphore.h`` header that will give us the primitives and data types for using them.

### Semaphore declaration, initialization, and destroy
Now, let us look at the ``mainSemaphore.c`` file that contains the function ``largestElement`` (in line 33), which is responsible for instantiating the threads. In that function, in line 38, we declared the ``sem_t semaphore`` variable, which we will use to synchronize the threads.

After the declaration, in line 50, we initialized the ``semaphore`` variable using the ``sem_init`` primitive. That primitive receives three parameters: the semaphore address, a flag to indicate if the semaphore is shared between threads (0) or if it is shared among processes (non zero), and the initial value (greater than or equal to zero). 

After initializing the semaphore, we can use it to block or unblock other threads, as we will describe later. Then, when we do not need the semaphore anymore, we can destroy it with the command ``sem_destroy``, as we did in line 94. 

### Structure to handle the parameters
For the thread to work, we will pass various parameters embedded in a structure defined in file ``searchThreadsSemaphore.h`` and replicated as follows.

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
Now, let us focus on the thread code in file ``searchThreadsSemaphore.c``, within the function ``searchLargestElementThread`` (in line 25). We first declare all the local variables to handle the parameters passed to the thread, including the semaphore and the structure to handle the largest element and its position.

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
The instructions for compiling are in the ``makefileSemaphore`` file. Therefore, to compile the code, you can issue the following make command.
```sh
make -f makefileSemaphore
```

To run the program, you can issue the command ``./searchThreadsSemaphore``.
