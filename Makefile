CC = gcc

OBJS = setup.c

OBJ_NAME = main

COMPILER_FLAGS = -Wall 

LINKER_FLAGS = -lm 

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
