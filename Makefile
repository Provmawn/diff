CC = clang
COMPILER_FLAGS = -g
OBJ = lcs.c main.c
OBJ_OUT = main

all : $(OBJ)
	$(CC) $(COMPILER_FLAGS) $(OBJ) -o $(OBJ_OUT)
