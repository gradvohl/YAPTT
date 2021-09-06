# Semaphores and mutexes example
In this section, we will show how to implement synchronization, one of them using semaphores and other using mutexes. As mention before, semaphores and mutexes are very alike. The difference is that semaphores can handle values greater or equal zero, while mutexes handle two states: lock and unlock.

## Problem description and the strategy to solve it
The problem is to search for the maximum value in an array of 40 non ordered random integers. Therefore, we will divide the array into four partitions and let each thread calculates the largest value in the partition assigned to it. 

In the end, each thread compares its largest integer found with a variable that handles the largest integer found so far. 
