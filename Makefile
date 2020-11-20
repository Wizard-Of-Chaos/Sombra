CC = g++
CFLAGS = -g -Wall

Astar: displaymap.o min_heap.o
	$(CC) -o Euclidean main.cpp displaymap.o min_heap.o
	$(CC) -o Manhattan main.cpp displaymap.o min_heap.o

displaymap.o: displaymap.cpp
	$(CC) -c displaymap.cpp

min_heap.o: min_heap.cpp
	$(CC) -c min_heap.cpp
clean:
	$ rm *.o Euclidean Manhattan
	$(CC) -c displaymap.cpp
	$(CC) -c min_heap.cpp
	$(CC) -o Euclidean main.cpp displaymap.o min_heap.o
	$(CC) -o Manhattan main.cpp displaymap.o min_heap.o
