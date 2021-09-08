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


