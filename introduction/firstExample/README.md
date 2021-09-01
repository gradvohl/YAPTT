# Time to Code
The code we will see is in the file ``firstExample.c``. It is quite simple and will create five threads. Each thread will print a message in the screen with its identification.

## The header
As the reader can see in the file ``firstExample.c``, in line 4, we included the ``pthread.h`` header. This header contains all the PThreads functions.

### The thread funcion
Now, turn your attention to lines 14 to 22. There, we implemented the ``printHello`` thread. Inside that function, the reader can see that in line 18 we used the function ``pthread_self`` to get the thread internal identification (id).  We rarely use this information inside a thread, but it is importante to know that each thread has an id and we can use the ids to syncronize the threads within the main function.

In the end of the thread, in line 21, notice that we call ``pthread_exit(NULL);`` That call will tell the main function that the thread finished and returns no address.

### The thread creation in the main funcion
As we stated before, each process has a main thread. Therefore, let us consider the main function. In line 26, we created an array with ``NUM_THREADS`` positions. This array will handle the threads ids, which we will use for joining the threads after their processing.

From line 30 to line 40, that loop will create five threads, one at each iteration. In line 33, we will use the function ``pthread_create`` to create the threads. The function ``pthread_create`` receives four arguments:
- The address of a variable to handle id of the created thread.
- The address of a structure with attributes for thread creation (we will use ``NULL`` to use the default attributes).
- The name of the function that embeds the thread.
- The address of the argument that we will pass for the thread (in this case, we will use ``NULL`` because we will not pass any parameters).

On success, ``pthread_create`` returns 0 to the ``rc`` variable. Then, in line 35, we test if variable ``rc`` has a value different from zero. If that is the case, we print a message in standard error output and leave the program.

If everything worked well, after line 40, we will have five threads running in parallel.

### The thread joining in the main funcion
Starting in line 42 until line 52, the main thread will wait for every other thread to join. Specifically in line 45, we used the function ``pthread_join`` to block the main thread until another specific thread finishes. The ``pthread_join`` receives two parameters:
- The id of the thread it will wait for.
- The address of a pointe to variable that will handle the result (in this case, we will use ``NULL`` because we do not expect that the thread will return data).

On success, ``pthread_join`` returns 0 to the ``rc`` variable. Then, in line 47, we test if variable ``rc`` has a value different from zero. If that is the case, we print a message in standard error output and leave the program.
