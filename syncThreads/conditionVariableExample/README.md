# Condition variable example
This section shows how to implement synchronization using a Condition Variable (CV). Unlike mutex and semaphore, which synchronize thread access to data, a condition variable is a way to signal that a condition happened to other threads. Therefore, the thread that received that signal may unblock itself and perform other operations.

In PThreads library, a CV always works together with a mutex. It works this way because when the CV receives a signal, it unlocks its associated mutex.

A solution using a condition variable will have the following pattern (considering two threads).

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
In this problem, we will start two threads. The first will remain blocked until the second thread signalizes that it generates a specific number (7). Then, the second thread will generate integers until it finds the number 7.

### Condition variable declaration, initialization, and destroy
As we mentioned before, it is necessary to declare a condition variable and a mutex. The second parameter is ``NULL`` because we will use the default attributes for the variables. Therefore, the commands are the following:

```c
pthread_cond_t cond;
pthread_mutex_t lock;

pthread_cond_init(&cond, NULL);
pthread_mutex_init(&lock, NULL);
```

Besides, before the end of the program, the program must destroy those variables with the following commands.

```c
pthread_cond_destroy(&cond);
pthread_mutex_destroy(&lock);
```

### Defining the mutual exclusion zone within the thread code
Let us take a look at the two threads, both in file ``rollDice.c``. The first thread (``void *blockedThread(void *args)``) will acquire a lock to guarantee access to the mutual exclusion zone. After that, it calls the ``pthread_cond_wait(cond, lock)`` primitive, which will block that thread, waiting for a signal carried by the ``cond`` variable. 

The thread must have the mutex locked by the calling thread, or undefined behavior will happen. So, that is the reason for acquiring the lock before.

```c
void *blockedThread(void *args)
{
  pthread_cond_t *cond;
  pthread_mutex_t *lock;

  cond = ((parameters *) args)->cond;
  lock = ((parameters *) args)->lock;

  pthread_mutex_lock(lock);
 
  fprintf(stdout, "Waiting on a condition variable.\n");
  pthread_cond_wait(cond, lock);

  pthread_mutex_unlock(lock);

  fprintf(stdout, "The other thread get a 7. I am out.\n");

  pthread_exit(NULL);
}
```

Now, let us focus on the ``void *generateNumbers(void *arg)`` thread. First, it will receive the address of the shared condition variable. Then, it will generate random numbers until it finds the number 7. After that, it will signalize it to the other thread using the ``pthread_cond_signal(cond);`` command.

```c
void *generateNumbers(void *arg)
{
  register unsigned int i;
  pthread_cond_t *cond;

  cond = ((pthread_cond_t *) arg);

  do {
      fprintf(stdout, "Number: %d\n", i = rand() % 8);
  } while (i != 7);

  fprintf(stdout, "I get a 7. Releasing the other thread!\n");
  pthread_cond_signal(cond);
  pthread_exit(NULL);
}
```


### Compiling and running the mutex code

The instructions for compiling are in the ``makefile`` file. Therefore, to compile the code, you can issue the following ``make`` command. 
```sh
make 
```

To run the program, you can issue the command ``./rollDice``.

# What's next?
Now, you can see how to implement synchronization using [Barriers](../barrierExample). Or, if you prefer, you can get back to the [main page](https://github.com/gradvohl/YAPTT).
