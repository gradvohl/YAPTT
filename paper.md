---
title: 'YAPTT -- Yet Another PThread Tutorial '
tags:
- Multithread programming
- Concurrent programming
- Synchronization
authors:
- name: Andre Leon S. Gradvohl
  orcid: 0000-0002-6520-9740
  affiliation: 1
affiliations:
- name: School of Technology, University of Campinas. Limeira, Sao Paulo, Brazil.
  index: 1
date: 10 October 2021
bibliography: paper.bib
---

# Summary
Concurrent programming is a topic that deserves more exploration in Computer Science undergraduate courses, especially in practical terms. Therefore, to contribute to teaching those practical aspects, this text presents yet another PThreads tutorial (YAPTT) for pure C programming language. We are aware that there are  are some tutorials on the world wide web that help programmers use PThreads API. However, we noticed that some PThreads tutorials do not approach techniques in a conceptually correct way. Some materials on the web appeal to quick code snippets that work, but distort a little from the original idea in PThreads library. Others do not get to the point and let the user get bogged down in the details. The goal of YAPTT is to offer one more resource to help those interested in learning about programming using the PThreads library using the pure C programming language. Some of the differentials of the YAPTT are that it is open source, has many examples, and can be adapted or supplemented by any user according to his/her needs. 

# Statement of Need
The Yet Another PThread Tutorial (YAPTT) supports learning multithreaded programming using the POSIX Threads API (PThreads). The PThreads API belongs to a family of standards called the Portable Operating System Interface (POSIX), specified by the IEEE Computer Society to maintain compatibility between operating systems.

YAPTT is entirely open and available on the GitHub code hosting platform. As a result, readers (students or instructors) can learn from the content and source code, add new examples, and improve the explanation of concepts. In this way, they can adapt the content to their needs.

The examples available in YAPTT are well documented and ready to be compiled and run. Besides, there was a concern to write correct code without appealing to code that works, but that somehow distorts the original idea of the PThreads API, as happens in other texts available on the web. Therefore, the strategies and code used in YAPTT can serve as a model for other more complex projects that use the PThreads API in C programming language.

# Target audience
I designed YAPTT for readers interested in writing code in the pure C programming language using the PThreads API. Therefore, YAPTT readers must be already familiar with using pointers and memory allocation in the C programming language.

Another issue worth mentioning is the fact that YAPTT uses the pure C programming language. It means that the YAPTT examples do not use code snippets compiled only with compilers for C++, for example. Instead, the reader can compile and generate the example codes using any C programming language compiler.

# Learning Objectives and Content
The learning objectives are as follows:

- Understand what threads are, what advantages and disadvantages a code with multiple threads might bring to the performance of a program.

- Learn how to instantiate multiple threads in a program that uses the PThreads API.

- Understand how to send arguments to a function that encapsulates a thread using the PThreads API.

- Understand how to receive values produced by a thread using the PThreads API.

- Master the four main thread synchronization mechanisms (semaphores, mutexes, condition variables, and barriers) using the PThreads API.

To achieve the learning objectives, I structured the content in the three sections described next.

1. Introduction: covering the main concepts behind the PThreads API.

2. Passing parameters to threads: explaining how to pass parameters to threads and get returns.

3. Synchronizing threads: showing how to synchronize threads using the thread synchronization mechanisms (semaphores, mutexes, condition variables, and barriers).

There are practical examples at the end of each section (or subsection), ready to compile and execute. I documented the source codes to facilitate understanding where the reader uses the PThreads API.

# Conclusion and Perspectives
My goal in creating YAPTT was to make available to the community an objective, practical tutorial that could be used by anyone interested in learning a little about the PThreads API. Obviously, we know that there are other tutorials available on the web. Still, we believe that YAPTT is different by being more objective, without presenting "half-cooked" solutions, that is, codes that work but are not fully in line with the PThreads API idea.

I expect that readers will widely use this tutorial. But, at the same time, I hope the material can be complemented by other users, always to help the whole community.

# References
