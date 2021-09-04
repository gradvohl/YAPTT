# Synchronizing threads
Most of the time, when we write multithread programs, we want to create a pool of threads to cooperate for solving a problem. However, for cooperation to occur, the threads must exchange information (communicate) with each other. Also, almost whenever we have communication, we need synchronization.

In this section, we will talk about some strategies for synchronization among threads. In this tutorial, we will focus on the following methods:
- Semaphores.
- Mutexes.
- Condition variables.
- Barriers.

The following table summarizes the methods we will approach, their utilization, and the operations each method uses.

|     | Semaphores | Mutexes | Condition variables | Barriers |
| --- | --- | --- | --- | --- |
| **Description** | Mechanism for signaling between threads. | Resource lock mechanism. | Mechanism to signal to another thread that a resource has become available. | Mechanism to signal to other threads that a point in the code has been reached. |
| **Variable Type** | ``sem_t`` | ``pthread_mutex_t`` | ``pthread_cond_t`` | ``pthread_barrier_t`` |
| **Initialization** | ``sem_init`` | ``pthread_mutex_init`` | ``pthread_cond_init`` | ``pthread_barrier_init`` |
| **Blocking** | ``sem_wait`` | ``pthread_mutex_lock`` | ``pthread_cond_wait`` | ``pthread_barrier_wait`` |
| **Unblocking** | ``sem_post`` | ``pthread_mutex_unlock`` | ``pthread_cond_signal`` | |
| **Desalocation** | ``sem_destroy`` | ``pthread_mutex_destroy`` | ``pthread_cond_destroy`` | ``pthread_barrier_destroy`` |





