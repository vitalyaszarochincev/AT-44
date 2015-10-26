CC = g++

CFLAGS = -c -Wall -g -fexceptions -pedantic

all: lab2

lab2: main.o param.o tasks.o fileProc.o
	$(CC) main.o param.o tasks.o fileProc.o -o lab2

main.o: main.cpp
	$(CC) $(CFLAGS) "main.cpp"

param.o: param.cpp
	$(CC) $(CFLAGS) "param.cpp"

tasks.o: tasks.cpp
	$(CC) $(CFLAGS) "tasks.cpp"

fileProc.o: fileProc.cpp
	$(CC) $(CFLAGS) "fileProc.cpp"

clean:
	rm -rf *.o lab2

