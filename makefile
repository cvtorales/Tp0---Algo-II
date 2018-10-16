# Archivo : makefile

CC = g++
FLAGS = -Wall -g -pedantic

all:tp1 clean

tp1: main.o cmdline.o Sensor.o RedSensores.o Query.o Data.o SegmentTree.o
	$(CC) $(FLAGS) -o tp1 main.o cmdline.o Sensor.o RedSensores.o Query.o Data.o SegmentTree.o

main.o: main.cpp main.h
	$(CC) $(FLAGS) -o main.o -c main.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(FLAGS) -o cmdline.o -c cmdline.cpp

Sensor.o: Sensor.cpp Sensor.h
	$(CC) $(FLAGS) -o Sensor.o -c Sensor.cpp

RedSensores.o: RedSensores.cpp RedSensores.h
	$(CC) $(FLAGS) -o RedSensores.o -c RedSensores.cpp

Query.o: Query.cpp Query.h
	$(CC) $(FLAGS) -o Query.o -c Query.cpp

Data.o: Data.cpp Data.h
	$(CC) $(FLAGS) -o Data.o -c Data.cpp

SegmentTree.o: SegmentTree.cpp SegmentTree.h
	$(CC) $(FLAGS) -o SegmentTree.o -c SegmentTree.cpp

clean:
	rm *.o
