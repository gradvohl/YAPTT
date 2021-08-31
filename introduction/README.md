# Introduction
In this section, we will give some basic information about how threads work using PThreads. Also, we will present the first examples, which explain the fundamental structures for writing codes for threads in PThreads.

I divided this section is the following topics:
- [Brief Overview of Threads](#Brief-Overview-of-Threads)
- [Schematic of Multithread Processing using PThreads](#Schematic-of-Multithread-Processing-using-PThreads)
- [Thread signature](#Thread-signature)

If the reader feels comfortable with the concepts behind threads, she/he can skip the text until the [Threads signatures](#Threads-signatures) section.


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

## Thread signature
Remember that functions embed threads. Also, in PThread API, to be a thread, a function should use the signature depicted in the following figure.

<img src="https://github.com/gradvohl/YAPTT/blob/main/introduction/ThreadSignature.png?raw=true" class="center" width=335 />

Notice that both the type of return and the argument for the function are ``void *``. That information means that the function may receive an address for anything as a parameter. Also, the function will return an address for anything.

It is important to mention that the programmer can specify the function name and the parameter's name the function will receive. However, the programmer cannot change the type of return nor the parameter the function gets.
