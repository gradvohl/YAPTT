# Time to code
In this section, we will ilustrate how to pass parameters to the threads and how to get the return of a thread using the PThread API. First, we will describe a problem to contextualize and motivate the parameters passing. After that, we will delve into the code.

## Problem description
We want to search for an element in an array with 40 integers in a random order. For that task, we will divide the array into four partitions, and let each thread search in a partition. 

If a thread finds the element, it will tell the others to stop searching and it will return the position of the element. If a thread do not find the element, it will return ``-1``. The main thread will collect the results of all threads ans will show the position of the element or "Element not found".

## Some information about the code
Although the example code is not that long, I made sure to separate it into different files. The goal is to facilitate the abstraction of concepts and, at the same time, to keep the code leaner. 

However, the reader need not worry, because the ``makefile`` has all the instructions for compiling the code. All the user has to do is issue the ``make`` command.

I divided the code into the following files:
- ``main.c`` with the main code, and the function ``searchElement`` responsible for instantiate the threads. 
- ``funcs.c`` and ``funcs.h`` with the code and respective header for auxiliary functions (create the arrays, search in arrays and so on). 
- ``searchThreads.c`` and ``searchThreads.h`` with the code and respective header for the threads.
