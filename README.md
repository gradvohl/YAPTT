# YAPTT -- Yet Another PThread Tutorial <img src="https://github.com/gradvohl/YAPTT/blob/main/figures/YAPTT.png?raw=true" align="right" width=283 />

By André Leon S. Gradvohl, Dr.

[gradvohl@unicamp.br](mailto://gradvohl@unicamp.br)

## Overview
This repository contains a new tutorial on the POSIX Threads (PThreads) application programming interface (API) using the C programming language. The PThreads API allows the programmer to create different streams of instructions (threads) that, if well-orchestrated, can get better performance from the processing cores in a processor.

I split this tutorial into sections stored in specific directories. Each section covers a particular subject related to the PThreads API. The reader can feel free to read the tutorial in the order that suits best. However, I suggest that the beginning reader take the following order of sections:

1. [Introduction](introduction): Main concepts behind the PThreads library and the first PThread program.
2. [Passing parameters to threads](passingParameters): How to pass parameters to threads and get returns from them.
3. [Synchronizing threads](syncThreads): How to synchronize threads.

## How to use the examples in YAPTT
Each section has a practical example to illustrate the approached concepts. All the examples in YAPTT are ready to be compiled and run after compilation in a **Linux** distribution. It is essential to have the [GNU Compiler Collection](http://gcc.gnu.org) installed in the reader's **Linux** operating system for compiling.

There is a ``makefile`` with the instructions for compiling the source codes in the directories where the examples are. When the user issues the ``make`` command, it will interpret the compilation instructions in the ``makefile``, building the program. The output of the ``make`` command itself shows the compiler and the respective parameters used for compiling each source code and linking modules together.

## Licensing
This work is licensed under a Creative Commons Attribution 4.0 International License.

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

The readers and instructors are free to share and adapt this material for their needs.
