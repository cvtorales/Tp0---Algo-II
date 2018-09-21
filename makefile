# Archivo : makefile

CC = g++
FLAGS = -Wall -g -pedantic

all:tp0 clean

tp0: main.o cmdline.o Sensor.o RedSensores.o Query.o
	$(CC) $(FLAGS) -o tp0 main.o cmdline.o Sensor.o RedSensores.o Query.o

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

clean:
	rm *.o
