# Barrier example
This section shows how to use barriers to provide synchronization in PThreads. In the synchronization context, the barrier is a point in the code of each of the threads such that all threads arriving at that point must be blocked until everyone arrives. After all threads arrive, they are all unblocked and can continue their execution after that point in their code. The following figure illustrates the synchronization with barriers. 

<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadBarriers.png?raw=true" class="center" width=327 />

The programmer may think that the ``pthread_join`` primitive is a type of barrier. That is a correct understanding. However, the ``pthread_join`` primitive signalizes that a thread is finished. 

In some situations, we need to implement a barrier to synchronize threads up to a point in their code, and let them continue after the barrier. In such situations, ``pthread_join`` primitive will not work.

Now, let us depict the use of barriers with an example problem in next section.

## Problem description and the strategy to solve it
In this problem, two threads will generate 100 integers to store in a single array. Each thread will generate 50 unrepeated integers in its array partition. After storing the numbers in the array, one of the threads will check and print the values that match in both partitions of the array.

Therefore, we will need a barrier to assure that both threads fill their partition before one of them search for matched values in the other partition.

### Barrier declaration, initialization, and destroy
First, it is necessary to declare a barrier and initialize it. We shall call the following code to declare and initialize a barrier variable.

```c
pthread_barrier_t barrier;
pthread_barrier_init(&barrier, NULL, NTHREADS)
```
Notice that the ``pthread_barrier_init`` primitive receives three parameters. First is the address of the barrier variable. The second parameter are the attributes. In most cases, we use ``NULL`` because we will use the default attributes for the variables. The third parameter is the number of threads that will wait in that barrier before all of them continues after the barrier.

Besides, before the end of the program, the program must destroy the barrier variable with the following commands.

```c
pthread_barrier_destroy(&barrier);
```

### Setting the barrier within the thread code
Let us take a look in the thread code in file ``generateAndCheck.c``. In line 47, we call the ``pthread_barrier_wait(barrier);`` function. In that point in code, a thread will stop and wait until all the threads that share the ``barrier`` variable call the ``pthread_barrier_wait`` primitive.

The ``pthread_barrier_wait`` primitive may return zero or ``PTHREAD_BARRIER_SERIAL_THREAD``. According to the manual, the constant ``PTHREAD_BARRIER_SERIAL_THREAD`` shall be returned to one unspecified thread and zero shall be returned to each of the remaining threads.

### Compiling and running the mutex code

The instructions for compiling are in the ``makefile`` file. Therefore, to compile the code, you can issue the following ``make`` command. 
```sh
make 
```

To run the program, you can issue the command ``./createAndCheck``.

# What's next?
We reached the end of the YAPTT tutorial. I hope you have learned a lot and that your knowledge will help develop better-performing programs.

If you want, you can get back to the [main page](https://github.com/gradvohl/YAPTT).
