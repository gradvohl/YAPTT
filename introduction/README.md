# Introduction
In this section, we will give some basic information about how threads work using PThreads. Also, we will present the first examples, which explain the fundamental structures for writing codes for threads in PThreads.

I divided this section is the following topics:
- [Brief Overview of Threads](#Brief-Overview-of-Threads)
- [Schematic of Multithread Processing using PThreads](#Schematic-of-Multithread-Processing-using-PThreads)
- [Thread Signature](#Thread-Signature)
- [Time to Code](#Time-to-Code)



## Brief Overview of Threads
Usually, when we write the code for a program, we consider that the processor will execute the instructions one at a time. However, the processor can execute some instructions (thread) in parallel, especially those with no dependencies. Dependence occurs when the result of one instruction influences the execution of another.

With the advent of symmetric processors, those consisting of multiple processing cores that access shared memory, core processors can execute threads in parallel. Thus, each instruction set (thread) can run in a different processing core and, in theory, have a faster program.

In practice, other factors can compromise the performance of a multithreaded program. For example, the programmer needs to consider the time the operating system spends creating a thread. Therefore, if the amount of processing a thread will have is not large enough, the operating system may spend more time creating the thread than the thread will spend processing.

This tutorial will show how to use a library for multiple threads programming in the Portable Operating System Interface (POSIX) standard. This library or Application Programming Interface (API) is called POSIX Threads (PThreads). Because it adopts a standard, it is possible to use it on any operating system that embraces POSIX, notably Linux.

I highlight that there are other APIs for multithreaded programming, for example, OpenMP. But other APIs use a different paradigm than PThreads. For example, a vital point in PThreads is that **each function embeds a thread**. This paradigm -- where a function encapsulates a thread -- allows for different granularity. That is, for the PThreads API, each thread has a reasonable set of instructions to execute.

## Schematic of Multithread Processing using PThreads
To illustrate how multiple threads work, let's consider the following figure. First, note that every process has a main thread (represented by the wavy line in the center of the process). Then, at some point in processing, this main thread can create a second thread by calling a specific function (in this case, the function ``pthread_create``).

<img src="https://github.com/gradvohl/YAPTT/blob/main/introduction/ThreadsBasics.png?raw=true" class="center" width=256 />

If everything went right in the function call, there would be two threads running simultaneously. However, if the process runs on a multicore processor, each thread will likely be on a different processor core.


The program can create as many threads as necessary. At the end of each thread, created using the default attributes, the threads can return to the main thread, returning a result of the processing or simply signaling that they have finished. A thread uses the function ``pthread_exit`` to signal that it has reached its end.

In turn, the main thread can wait for the secondary threads to finish with the ``pthread_join`` function, which blocks the main thread until the indicated thread finishes.

## Thread Signature
Remember that functions embed threads. Also, in PThread API, to be a thread, a function should use the signature depicted in the following figure.

<img src="https://github.com/gradvohl/YAPTT/blob/main/introduction/ThreadSignature.png?raw=true" class="center" width=335 />

Notice that both the type of return and the argument for the function are ``void *``. That information means that the function may receive an address for anything as a parameter. Also, the function will return an address for anything.

It is important to mention that the programmer can specify the function name and the parameter's name the function will receive. However, the programmer cannot change the type of return nor the parameter the function gets.

## Time to Code
Now, let us see some code in action. Our first example is in the ``firstExample`` directory and I invite the reader to look at the code, before compiling it. The code in the file ``firstExample.c`` is quite simple. It will create five threads and each thread will print a message in the screen with its identification.

### The header
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
