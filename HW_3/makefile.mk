CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=main.o stack.o student.o
EXEC=prog.exe
RM=rm -rf *.o *.exe

# The first rule is invoked by default
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe

# Full syntax
# Custom Shell commands

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
	
student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c
	
main.o: main.c stack.h student.h
	$(CC) $(CFLAGS) -c main.c


# Custom rule - we can invoke it manually
# by running "make clean"
clean:
	$(RM)
	
