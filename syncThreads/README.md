# Synchronizing threads
Most of the time, when we write multithread programs, we want to create a pool of threads to cooperate for solving a problem. However, for cooperation to occur, the threads must exchange information (communicate) with each other. 

The communication among threads occurs using shared variables. Since a process can handle multiple threads, using a global scope variable is practical to share a variable among threads. However, I am not particularly eager to use global variables for several reasons (namespace pollution, possible alteration in other parts of the code etc). Therefore, the alternative is to dynamically allocate a memory location and share the address of that memory location among the threads.

Either way, every time threads share an object (variables, memory locations, open files etc), that object is in the core of the code's **critical region**. As the name suggests, a critical region should have exceptional attention by the programmer, especially when an operation (or a set of operations) can change the contents of a shared object in a critical region. Therefore, the programmer should create a **mutual exclusion zone** to ensure that only one thread at a time performs its operations at shared objects inside that critical region. The procedure in which a thread signals that other threads should wait for an operation to complete before continuing is synchronization.

In few words, creating a mutual exclusion zone in a code involves using commands to block a thread just before the zone and unblock the other threads after the zone. Blocking and unblocking operations require a shared variable (or memory location) among threads.

The programmers must be careful about the mutual exclusion zones they define. Mutual exclusion zones can degrade the program's performance since threads must wait before accessing the zone. On the other hand, creating fewer mutual exclusion zones than necessary can lead to inconsistencies in shared objects.

## Strategies for threads synchronization
In this section, we will talk about some strategies for synchronization among threads. In this tutorial, we will focus on the following methods:
- Semaphores.
- Mutexes.
- Condition variables.
- Barriers.

The following table summarizes the methods we will approach, their utilization, and each method's operations.

|     | Semaphores | Mutexes | Condition variables | Barriers |
| --- | --- | --- | --- | --- |
| **Description** | Mechanism for signaling between threads. | Resource lock mechanism. | Mechanism to signal to another thread that a resource has become available. | Mechanism to signal to other threads that it reaches a point in the code. |
| **Variable Type** | ``sem_t`` | ``pthread_mutex_t`` | ``pthread_cond_t`` | ``pthread_barrier_t`` |
| **Initialization** | ``sem_init`` | ``pthread_mutex_init`` | ``pthread_cond_init`` | ``pthread_barrier_init`` |
| **Blocking** | ``sem_wait`` | ``pthread_mutex_lock`` | ``pthread_cond_wait`` | ``pthread_barrier_wait`` |
| **Unblocking** | ``sem_post`` | ``pthread_mutex_unlock`` | ``pthread_cond_signal`` | |
| **Desalocation** | ``sem_destroy`` | ``pthread_mutex_destroy`` | ``pthread_cond_destroy`` | ``pthread_barrier_destroy`` |

It is worth mentioning that, except for synchronization using semaphores, all the other methods are already part of the PThreads API.

The reader can observe that the methods follow a life cycle: 
- Initialize the variables. 
- Block before entering the mutual exclusion zone;
- Unblock after leaving the mutual exclusion zone; and 
- Deallocate the variables. 

Also, it is essential to consider that the variables used in all those methods are operating system resources. Therefore, the programmer must allocate (initialize) them at the beginning of their use and deallocated them when no longer needed. 

## Semaphores and Mutexes
Semaphores and Mutexes are very alike. The main difference is that mutexes are binary variables, assuming two states: locked or unlocked. In turn, semaphores can work with any non-negative value (i. e., values greater than or equal to zero). So, when a semaphore reaches zero, it will block the thread.

Directory [mutexAndSemaphorExamples](mutexAndSemaphorExamples) will present two different examples, one using Semaphore and the other using Mutex.

## Condition variables
As the name suggests, condition variables block a thread until a particular condition becomes true. Therefore, we use
condition variables as a notification system between threads. 

However, it is important to mention that there is no guarantee that the desired condition still exists after the unlocking. So, the programmer should check if the thread met the desired condition.

Directory [conditionVariableExample](conditionVariableExample) brings an example for condition variables.

## Barriers
Barriers are a method to synchronize a group of threads at some point in each thread code. When all the threads reach a barrier, it will release them.

Directory [barrierExample](barrierExample) brings an example for barriers.

# What's next?
Now, you can see examples of synchronization using [Semaphores and Mutexes](mutexAndSemaphorExamples), [Condition variables](conditionVariableExample) or [Barriers](barrierExample). Or, if you prefer, you can get back to the [main page](https://github.com/gradvohl/YAPTT).
