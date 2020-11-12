CC = g++
CFLAGS = -g -Wall

Sombra: displaymap.o
	$(CC) -o Sombra main.cpp displaymap.o

displaymap.o: displaymap.cpp
	$(CC) -c displaymap.cpp