# Archivo : makefile

CC = g++
FLAGS = -W -Wall -g -pedantic

all:tp0 clean

tp0: main.o cmdline.o Sensor.o RedSensores.o Query.o Calculos.o
	$(CC) $(FLAGS) -o tp0 main.o cmdline.o Sensor.o RedSensores.o Query.o Calculos.o

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

Calculos.o: Calculos.cpp Calculos.h
	$(CC) $(FLAGS) -o Calculos.o -c Calculos.cpp

clean:
	rm *.o
