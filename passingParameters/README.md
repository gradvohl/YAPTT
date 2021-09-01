## Passing parameters to threads
Passing parameters to threads is a bit tricky when compared to passing parameters to regular functions. As the reader may be aware, in C language parameters are passed by value. In special ocasions, the programmer can specify that a function receives address (stored in pointers) as arguments. Nevertheless, using pointers a programmer can implement parameters passing by reference.

As mentioned in the section [Thread Signature](../introduction/README.md#Thread-Signature), a thread receives a single ``void *`` parameter and returns a ``void *`` type. Besides, it is important to remember that ``void *`` means a "pointer to anything". Therefore, we can encapsulate any set of data into a structure and pass (or receive) the address of that structure to (or from) a thread.


