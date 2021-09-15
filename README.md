# YAPTT -- Yet Another PThread Tutorial <img src="https://github.com/gradvohl/YAPTT/blob/main/figures/YAPTT.png?raw=true" align="right" width=283 />
## Overview
This repository contains a new tutorial on the POSIX Threads library (PThreads) using the C language (pure, not C++). The PThreads library allows you to create different streams of instructions (threads) that, if well-orchestrated, can get better performance from the processing cores in a processor.

I split this tutorial into sections, and each section is in a specific directory. Each section covers a particular subject related to the PThreads library. The reader can feel free to read the tutorial in the order that suits him best. However, I suggest that the beginning reader follow the order of sections below:

1. [Introduction](introduction): Main concepts behind the PThreads library and the first PThread program.
2. [Passing parameters to threads](passingParameters): How to pass parameters to threads and get returns.
3. [Synchronizing threads](syncThreads): How to synchronize threads.

## How to use the examples in YAPTT
All the examples in YAPTT are ready to be compiled and run after compilation in a **Linux** distribution. For compiling, it is essential to have the [GNU Compiler Collection](http://gcc.gnu.org) installed in your **Linux** operating system.

In each directory, you have a ``makefile`` with the instructions for compiling the source codes. When the user issues the the ``make`` command, it will interpret the compilation instructions in the ``makefile``, building the program. The output of the ``make`` command itself shows the compiler and the respective parameters used for compiling each source code and linking modules together.

Shield: [![CC BY 4.0][cc-by-shield]][cc-by]

This work is licensed under a
[Creative Commons Attribution 4.0 International License][cc-by].

[![CC BY 4.0][cc-by-image]][cc-by]

[cc-by]: http://creativecommons.org/licenses/by/4.0/
[cc-by-image]: https://i.creativecommons.org/l/by/4.0/88x31.png
[cc-by-shield]: https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg

