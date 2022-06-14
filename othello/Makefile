CC = gcc
FLAGS = -g -Wall

all: main.o othello.o
	$(CC) $(FLAGS) -o main main.o othello.o

main.o: main.c othello.h
	$(CC) $(FLAGS) -c main.c

othello.o: othello.h

clean:
	rm *.o main