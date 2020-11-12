CC = g++
CFLAGS = -g -Wall

Euclidean: displaymap.o
	$(CC) -o Euclidean main.cpp displaymap.o

displaymap.o: displaymap.cpp
	$(CC) -c displaymap.cpp
