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
while ( Condition is false )
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
pthread_mutex_unlock(&lock)
```


## Problem description and the strategy to solve it
In this problem, we have two threads. The first of them will remain blocked until the second thread signalizes that it generates a specific number (7). 

### Condition variable declaration, initialization, and destroy


### Defining the mutual exclusion zone within the thread code


### Compiling and running the mutex code

The instructions for compiling are in the ``makefileMutex`` file. Therefore, to compile the code, you can issue the following ``make`` command. 
```sh
make -f makefileMutex
```

To run the program, you can issue the command ``./searchThreadsMutex``.

Next, we will see the solution using semaphores. Again, the program structure is the same, and only the synchronization primitives are different.
