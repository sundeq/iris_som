CC = gcc

OBJS = main.cpp

OBJ_NAME = main

COMPILER_FLAGS = -Wall

LINKER_FLAGS = 

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
