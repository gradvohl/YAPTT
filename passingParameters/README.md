# Passing parameters to threads

Passing parameters to threads in PThreads API is tricky compared to passing parameters to regular functions. As the reader may be aware, functions receive parameters passed by value in the C programming language. However, the programmer can specify that a function receives an address (stored in a pointer) as argument to mimic passage by reference. 

As mentioned in the section [Thread Signature](../introduction/README.md#Thread-Signature), a thread receives a single ``void *`` parameter and returns a ``void *`` type. Besides, it is important to remember that ``void *`` means a "pointer to anything". Therefore, we can encapsulate any data set into a structure and pass (or receive) the address of that structure to (or from) a thread.

The following figures may better explain the idea. Also, let us explain the steps, one at a time.
- The first step is to define a structure to handle all the parameters. I use the ``typedef`` keyword to define the structure, and I do it outside the scope of functions (usually in a header file).
- The next step is to dynamically create the structure in the memory (using ``malloc`` or any similar command) and fill the fields in the structure. The following figure shows how these data are in memory after allocation. Notice that the variable ``pointer`` in the figure has the address of the structure in the memory. 
<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadArgPassing1.png?raw=true" class="center" width=156 />

- The last step is to pass the variable ``pointer`` to the thread in the last argument of the ``pthread_create`` primitive, as shown in the following figure. 
<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadArgPassing2.png?raw=true" class="center" width=156 />

# Receiving the return of a thread
We can use similar reasoning for returning data from a thread in PThreads API. If necessary, we can define a structure to encapsulate all the data we want to return, allocate that structure dynamically within the thread, and return the address in the memory of that structure.

I want to highlight that all local variables, i. e. the variables declared inside a function, will vanish as soon as the function finishes (returns). Therefore, the programmer cannot return the address of local variables.

# Time to code
Let us see how parameter passing works in PThreads API with an example in directory [searchThreads](searchThreads). Or, if you prefer, you can get back to the [main page](https://github.com/gradvohl/YAPTT).
