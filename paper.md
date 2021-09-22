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
Concurrent programming is a topic that deserves more exploration in Computer Science undergraduate courses, especially in practical terms. Therefore, to contribute to teaching those practical aspects, this text presents the Yet Another PThreads Tutorial (YAPTT) for pure C programming language. We are aware that exists tutorials on the world wide web that help programmers use PThreads API. However, we noticed that some PThreads tutorials do not approach techniques in a conceptually correct way. Some materials on the web appeal to quick code snippets that work but distort a little from the original idea in the PThreads library. Others do not get to the point and let the user get bogged down in the details. The goal of YAPTT is to offer one more resource to help those interested in learning about programming using the PThreads library using the pure C programming language. The YAPTT is open source, has many examples, and can be adapted or supplemented by any programmer according to her/his needs.

# Statement of Need
The Yet Another PThread Tutorial (YAPTT) supports learning multithreaded programming using the POSIX Threads API (PThreads). The PThreads API belongs to a family of standards called the Portable Operating System Interface (POSIX), specified by the IEEE Computer Society to maintain compatibility between operating systems [@butenhof_programming_1997]. Besides, the PThreads library comes with the GNU Compiler Collection, common in most Linux distributions. These features make it easy and justifiable to use YAPTT as supplementary material for Operating Systems or Concurrent Programming courses at the undergraduate level or an Advanced Linux Programming course [@mitchell_advanced_2001].

YAPTT is entirely open and available on the GitHub code hosting platform. As a result, readers (students or instructors) can learn from the content and source code, add new examples, and improve the explanation of concepts. In this way, they can adapt the content to their needs.

The examples available in YAPTT are well documented and ready to be compiled and run. Besides, there was a concern to write correct code without appealing to code that works, but that somehow distorts the original idea of the PThreads API, as happens in other texts available on the web. Therefore, the strategies and code used in YAPTT can serve as a model for other more complex projects that use the PThreads API in the C programming language.

# Target audience
We designed YAPTT for readers interested in writing code in the pure C programming language using the PThreads API. Therefore, YAPTT readers must be already familiar with using pointers and memory allocation in the C programming language.

Another issue worth mentioning is the fact that YAPTT uses the pure C programming language. It means that the YAPTT examples do not use code snippets compiled only with compilers for C++, for example. Instead, the reader can compile and generate the example codes using any C programming language compiler.

# Learning Objectives and Content
The learning objectives are as follows:

- Understand what threads are, what advantages and disadvantages a code with multiple threads might bring to the performance of a program.

- Learn how to instantiate multiple threads in a program that uses the PThreads API.

- Understand how to send arguments to a function that encapsulates a thread using the PThreads API.

- Understand how to receive values produced by a thread using the PThreads API.

- Master the four main thread synchronization mechanisms (semaphores, mutexes, condition variables, and barriers) using the PThreads API.

To achieve the learning objectives, we structured the content in the three sections described next.

1. Introduction: covering the main concepts behind the PThreads API.

2. Passing parameters to threads: explaining how to pass parameters to threads and get returns.

3. Synchronizing threads: showing how to synchronize threads using the thread synchronization mechanisms (semaphores, mutexes, condition variables, and barriers).

There are practical examples at the end of each section (or subsection), ready to compile and execute. In addition, we documented the source codes to facilitate understanding where the reader uses the PThreads API.

# Conclusion and Perspectives
Our goal in creating YAPTT was to make an objective, practical tutorial available to the community that anyone interested in learning a little about the PThreads API can use. We know that there are many books, such as [@lewis_threads_1996,@butenhof_programming_1997,@mitchell_advanced_2001], that cover the subject with great quality and depth. Still, we believe that YAPTT is different from other tutorials in the web by being more objective, without presenting "half-cooked" solutions, that is, codes that work but are not fully in line with the PThreads API idea.

We expect that readers will widely use YAPTT. But, at the same time, we hope the material can be complemented by other users, always to help the whole community.

# References
