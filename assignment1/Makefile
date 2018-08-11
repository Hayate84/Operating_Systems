CC = g++
FLAGS = -c
INCLUDE = -I ./include
OBJECTS = ./build/*.o

producer_consumers: ./build/PClock.o ./build/main.o
	$(CC) -o $@ $(OBJECTS) -lpthread 
	mv producer_consumers ./bin/producer_consumers

./build/PClock.o: ./src/PClock.cc ./include/PClock.h
	$(CC) $(FLAGS) ./src/PClock.cc $(INCLUDE)
	mv PClock.o ./build/PClock.o

./build/main.o: ./src/main.cc
	$(CC) $(FLAGS) ./src/main.cc $(INCLUDE)
	mv main.o ./build/main.o

clean:
	rm ./build/*.o
	rm ./bin/*
