# Makefile for the searchThreads program.
#
# Author: Andre Leon S. Gradvohl, Dr.
#
# Program name
MAIN=searchThreads
# Defaultcompiler.
CC=gcc
#
# Aditional compiler flags.
CCFLAGS=-Wall 
#
# Additional libraries
LIBS=-pthread $(PROJECTLIB)
# 
# Source files
SOURCES=main.c searchThreads.c funcs.c
#
# Header files
HEADERS=searchThreads.h funcs.h
#
# Object files
OBJECTS=$(SOURCES:.c=.o)
#
# Directory where the program will be created.
PROGRAMDIR=.
#
# Compiler dependencies
all: $(MAIN)

$(MAIN): $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(PROGRAMDIR)/$(MAIN)

# For each .c file, compile according to the following rule
# and generate .o file.
# $<: the name of the prerequisite of the rule (a .c file).
# $@: the name of the target of the rule (a .o file).
.c.o: 
	$(CC) $(CCFLAGS) $(INCLUDES) $(LIBS) -c $<  -o $@

# Cleaning
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(PROGRAMDIR)/$(MAIN)

