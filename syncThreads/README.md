# Synchronizing threads
Most of the time, when we write multithread programs, we want to create a pool of threads to cooperate for solving a problem. However, for cooperation to occur, the threads must exchange information (communicate) with each other. Also, almost whenever we have communication, we need synchronization.

In this section, we will talk about some strategies for synchronization among threads. In this tutorial, we will focus on the following methods:
- Semaphores.
- Mutexes.
- Condition variables.
- Barriers.

The following table summarizes the methods we will approach, their utilization, and the operations each method uses.

| |Semaphores|Mutexes|Condition variables|Barriers
|---|---|---|---|---|
|Description| Mecanismo para sinalizar às demais threads que um ponto do código foi atingido | Mecanismo para sinalizar às demais threads que um ponto do código foi atingido | Mecanismo para sinalizar às demais threads que um ponto do código foi atingido |Mecanismo para sinalizar às demais threads que um ponto do código foi atingido|
|Variable Type | sem_t |pthread_mutex_t|pthread_cond_t|pthread_barried_t|





