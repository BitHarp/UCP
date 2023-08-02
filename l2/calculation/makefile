CC = gcc# define compiler to use
CFLAGS = -Wall -ansi -pedantic# include compile flags
OBJ = main.o calculation.o# all prerequisite .o files
EXEC = myProgram# name of executable

# ::LAYOUT::
# target file: preqruisite files(s)
# 	recipe (compile command)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c calculate.h
	$(CC) $(CFLAGS) main.c -c

calculation.o: calculation.c calculate.h
	$(CC) $(CFLAGS) calculation.c -c

clean:
	rm $(EXEC) $(OBJ)
