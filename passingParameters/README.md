## Passing parameters to threads

Passing parameters to threads is a bit tricky when compared to passing parameters to regular functions. As the reader may be aware, in the C language parameters are passed by value. In special ocasions, the programmer can specify that a function receives address (stored in pointers) as arguments. Nevertheless, using pointers a programmer can implement parameters passing by reference.

As mentioned in the section [Thread Signature](../introduction/README.md#Thread-Signature), a thread receives a single ``void *`` parameter and returns a ``void *`` type. Besides, it is important to remember that ``void *`` means a "pointer to anything". Therefore, we can encapsulate any set of data into a structure and pass (or receive) the address of that structure to (or from) a thread.

The following figures may better explain the idea. Also, let us explain the steps, one at a time.
1. The first step is to define a structure to handle all the parameters. Personally, I like to use the ``typedef`` keyword for defining the structure and I do it outside the scopes of functions (usually in my own header file).
2. Next step is to dynamically create the structure in the memory (using ``malloc`` or any similar command) and fill the fields in the structure. the following figure shows how these data are in memory after steps 1 and 2. Notice that the variable ``pointer`` in the figure has the address of the structure in the memory.
<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadArgPassing1.png?raw=true" class="center" width=156 />
3. The last step is to pass the variable ``pointer`` to the thread in the last argument of the ``pthread_create`` function, as shown in the following figure.
<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadArgPassing2.png?raw=true" class="center" width=156 />
