## Passing parameters to threads

Passing parameters to threads is a bit tricky when compared to passing parameters to regular functions. As the reader may be aware, in the C language parameters are passed by value. In special ocasions, the programmer can specify that a function receives address (stored in pointers) as arguments. Nevertheless, using pointers a programmer can implement parameters passing by reference.

As mentioned in the section [Thread Signature](../introduction/README.md#Thread-Signature), a thread receives a single ``void *`` parameter and returns a ``void *`` type. Besides, it is important to remember that ``void *`` means a "pointer to anything". Therefore, we can encapsulate any set of data into a structure and pass (or receive) the address of that structure to (or from) a thread.

The following figures may better explain the idea. Also, let us explain the steps, one at a time.
1. The first step is to define a structure to handle all the parameters. Personally, I like to use the ``typedef`` keyword for defining the structure and I do it outside the scopes of functions (usually in my own header file).
2. 

<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadArgPassing1.png?raw=true" class="center" width=312 />

3
<img src="https://github.com/gradvohl/YAPTT/blob/main/figures/ThreadArgPassing2.png?raw=true" class="center" width=312 />
