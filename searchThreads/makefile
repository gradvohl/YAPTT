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
# Include directory
AUXFUNCSDIR=../aux
INCLUDES=-I$(AUXFUNCSDIR)
#
# Additional libraries
PROJECTLIB=-L$(AUXFUNCSDIR)
LIBS=-pthread $(PROJECTLIB)
# 
# Source files
SOURCES=main.c searchThreads.c $(AUXFUNCSDIR)/funcs.c
#
# Header files
HEADERS=searchThreads.h $(AUXFUNCSDIR)/funcs.h
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

.c.o: 
	$(CC) $(CCFLAGS) $(INCLUDES) $(LIBS) -c $<  -o $@

# Cleaning
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(PROGRAMDIR)/$(MAIN)

