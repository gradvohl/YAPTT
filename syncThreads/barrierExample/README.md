# Barrier example
This section shows how to use barriers to provide synchronization in PThreads. In the synchronization context, the barrier is a point in the code of each of the threads such that all threads arriving at that point must be blocked until everyone arrives. After all threads arrive, they are all unblocked and can continue their execution after that point in their code. The following figure illustrates the synchronization with barriers 

<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadBarriers.png?raw=true" class="center" width=327 />

The programmer may think that the ``pthread_join`` primitive is a type of barrier. That is a correct understanding. However, the ``pthread_join`` primitive signalizes that a thread is finished. 

In some situations, we need to implement a barrier to synchronize threads up to a point in their code, and let them continue after the barrier. In such situations, ``pthread_join`` primitive will not work.

Now, let us depict the use of barriers with an example problem in next section.

## Problem description and the strategy to solve it
In this problem, two threads will generate 100 integers to store in a single array. Each thread will generate 50 unrepeated integers in its array partition.

After creating the array, each thread will check if . 


The first of them will remain blocked until the second thread signalizes that it generates a specific number (7). 

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
Let us take a look in the two threads, both in file ``rollDice.c``. In the first thread (``void *blockedThread(void *args)``), it will first acquire a lock to guarantee the access to the mutual exclusion zone. After that, it calls the ``pthread_cond_wait(cond, lock)`` primitive, which will block that thread, waiting for a signal carried by the ``cond``variable. 

It is important that the thread has the mutex locked by the calling thread or and undefined behavior will happen. That is the reason for acquiring the lock before.

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

Now, let us focus on the ``void *generateNumbers(void *arg)`` thread. First, it will receives the address of the shared condition variable. Then, it will generates random numbers until it finds the number 7. After that, it will signalizes it to the other thread using the ``pthread_cond_signal(cond);`` command.

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
