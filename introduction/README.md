## Introduction
Usually, when we write the code for a program, we consider that the processor will execute the instructions one at a time. However, the processor can execute some sets of instructions (threads) in parallel, especially those with no dependencies. Dependence occurs when the result of one instruction influences the execution of another.

With the advent of symmetric processors, those consisting of multiple processing cores that access shared memory, core processors can execute threads in parallel. Thus, each instruction set (thread) can run in a different processing core and, in theory, have a faster program.

In practice, other factors can compromise the performance of a multi-threaded program. For example, the programmer needs to consider the time the operating system spends creating a thread. Therefore, if the amount of processing that a thread will have is not large enough, the operating system may spend more time creating the thread than the thread will spend processing.

This tutorial will show how to use a library for multiple threads programming in the Portable Operating System Interface (POSIX) standard. This library or Application Programming Interface (API) is called POSIX Threads (PThreads). Because it adopts a standard, it is possible to use it on any operating system that embraces POSIX, notably Linux.

I highlight that there are other APIs for multithreaded programming, for example, OpenMP. But other APIs use a different paradigm than PThreads. For example, an vital point in PThreads is that each thread is embedded in a function. This paradigm -- where a function encapsulates a thread -- allows for different granularity. That is, for the PThreads API, each thread has a reasonable set of instructions to execute.




