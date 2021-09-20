# Time to Code
The code we will see is in the file ``firstExample.c``. It is pretty simple and will create five threads. Each thread will print a message on the screen with its identification.

If you want to go straight to the instructions for compiling and executing, go to section [Compiling and running](#Compile-and-running).

## The header
As the reader can see in the file ``firstExample.c``, in line 6, we included the ``pthread.h`` header. This header contains all the PThreads API functions calls and definitions needed.

## The thread function
Now, turn your attention to lines 14 to 22 (depicted as follows). There, we implemented the ``printHello`` thread. Inside that function, the reader can see that in line 18, we used the function ``pthread_self`` to get the thread internal identification (id).  We rarely use this information inside a thread, but it is important to know that each thread has an id, and we can use the ids to synchronize the threads within the main function.

```c
void *printHello(void *args)
{
  pthread_t id;

  id = pthread_self();
  fprintf(stdout, "Hello world! My thread id: #%ld\n", id);

  pthread_exit(NULL);
}
```

At the end of the thread, in line 21, notice that we call the ``pthread_exit(NULL);`` primitive. That primitive will tell the main function that the thread finished and returns no address (``NULL``). 

However, suppose a thread needs to return a value. In that case, the programmer must inform in this primitive the address of the variable that stores the value. We will talk about returning values in [another section](../../passingParameters).

## The thread creation in the main function
As we stated before, each process has a main thread. Therefore, let us consider the main function. In line 26, we created an array with ``NUM_THREADS`` positions. That array will handle the threads' ids, which we will use to join the threads after their processing.

From line 33 to line 43 (depicted as follows), that loop will create five threads, one at each iteration. In line 36, we will use the primitive ``pthread_create`` to instantiate the threads. The primitive ``pthread_create`` receives four arguments:
- The address of a variable to handle the created thread id.
- The address of a structure with attributes for thread creation (we will use ``NULL`` to use the default attributes).
- The name of the function that embeds the thread.
- The address of the argument that we will pass for the thread (in this case, we will use ``NULL`` because we will not pass any arguments).

```c
for (t = 0; t < NUM_THREADS; t++)
{
  fprintf(stdout, "Starting thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, printHello, NULL);

  if (rc)
  {
    fprintf(stderr, "ERROR: pthread_create() returns %d\n", rc);
    exit(EXIT_FAILURE);
  }
}
```

On success, ``pthread_create`` returns 0 to the ``rc`` variable. Then, in line 38, we test if variable ``rc`` has a value different from zero. If that is the case, we print a message in standard error output and leave the program.

If everything works well, after line 43, we will have six threads running in parallel. If the processor has six or more cores, it is possible that each core runs a different thread.

## The thread joining in the main function
Starting in line 48 until line 58 (presented as follows), the main thread will wait for every other thread to join. Specifically in line 51, we used the primitive ``pthread_join`` to block the main thread until another specific thread finishes. The ``pthread_join`` primitive receives two parameters:
- The id of the thread it will wait for.
- The address of a pointe to variable that will handle the result (in this case, we will use ``NULL`` because we do not expect that the thread will return data).

```c
for (t = 0; t < NUM_THREADS; t++)
{
  printf("Joining thread #%d\n", t);
  rc = pthread_join(threads[t], NULL);

  if (rc)
  {
    fprintf(stderr, "ERROR: pthread_join() returns %d\n", rc);
    exit(EXIT_FAILURE);
  }
}
```

On success, ``pthread_join`` returns 0 to the ``rc`` variable. Then, in line 53, we test if variable ``rc`` has a value different from zero. If that is the case, we print a message in standard error output and leave the program.

# Compiling and running
To compile this code, you can use the following command line:
```bash
gcc -pthread firstExample.c -o ./firstExample
```
In that command line, we have the following information:
- ``gcc`` is the compiler.
- ``-pthread`` indicates the use of the PThread API.
- ``firstExample.c`` is the source code.
- ``-o firstExample`` informs that the compiler should generate a program named ``firstExample``.

To run the program, you can issue the ``./firstExample`` command.

I also provided a ``makefile`` with automatic instructions for compiling. In that case, you can simply issue the ``make`` command to compile the source code.

# What's next?
Now, you can see how to [pass parameters to threads and get returns](../../passingParameters). Or, if you prefer, you can get back to the [main page](https://github.com/gradvohl/YAPTT).
