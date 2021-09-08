# Semaphores and mutexes example
This section shows how to implement synchronization, one of them using semaphores and the other using mutexes. As mention before, semaphores and mutexes are very alike. The difference is that semaphores can handle values greater or equal to zero, while mutexes handle two states: lock and unlock.

## Problem description and the strategy to solve it
The problem is to search for the maximum value in an array of 40 non-ordered random integers. Therefore, we will divide the array into four partitions and let each thread calculates the largest value in the partition assigned to it. 

In the end, each thread compares its largest integer found with a shared variable (a structure) that handles the largest integer found so far and its position in the array. After all the threads finish, the main thread will print the largest integer and its position in the array.

As the reader may suspect, that shared variable is a **critical region**. Therefore, we should create a **mutual exclusion zone** around this critical region to ensure that only one thread at a time will query and, if necessary, change the value of this variable.

First, we will present the solution using [semaphores](#Semaphore-solution). After, we will present the solution using [mutexes](#Mutex-solution). The programs are very similar. The main difference is in the commands used to establish the mutual exclusion zone.

## Semaphore solution
The
