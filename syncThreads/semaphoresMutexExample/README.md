# Synchronizing threads
Most of the time, when we write multithread programs, we want to create a pool of threads to cooperate for solving a problem. However, for cooperation to occur, the threads must exchange information (communicate) with each other. Also, almost whenever we have communication, we need synchronization.

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


The reader can observe that the methods follow a life cycle: initialize the variables, block and unblock, deallocate the variables. Also, it is important to notice that the variables used in all those methods are operating system resources. Therefore, the programmer must allocate (initialize) them at the beginning of their use and deallocated them when no longer needed.

## Semaphores and Mutexes
Semaphores and Mutexes are very alike. The main difference is that mutexes are binary variables, assuming two states: locked or unlocked. In turn, semaphores can work with any non-negative value (i. e., values greater than or equal to zero). So, when a semaphore reaches zero, it will lock the thread.

Section XXX will present examples for using Semaphores and Mutexes.

## Condition variables
As the name suggests, condition variables block a thread until a particular condition becomes true. Therefore, we use
condition variables as a notification system between threads. 

However, it is important to mention that there is no guarantee that the desired condition still exists after the unlocking. So, the programmer should check if the thread met the desired condition.

Section ZZZ brings an example for Condition variables.

## Barriers
Barriers are a method to synchronize a group of threads at some point in each thread code. When all the threads reach a barrier, it will release them.

Section WWW brings an example of barriers.
