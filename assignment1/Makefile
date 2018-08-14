CC = g++
FLAGS = -c
INCLUDE = -I ./include
OBJECTS = ./build/*.o

producer_consumers: ./build/PClock.o ./build/main.o ./build/printFunctions.o ./build/Init.o
	$(CC) -o $@ $(OBJECTS) -lpthread 
	mv producer_consumers ./bin/producer_consumers

./build/PClock.o: ./src/PClock.cc ./include/PClock.h
	$(CC) $(FLAGS) ./src/PClock.cc $(INCLUDE)
	mv PClock.o ./build/PClock.o

./build/printFunctions.o: ./src/printFunctions.cc ./include/printFunctions.h
	$(CC) $(FLAGS) ./src/printFunctions.cc $(INCLUDE)
	mv printFunctions.o ./build/printFunctions.o

./build/Init.o: ./src/Init.cc ./include/Init.h
	$(CC) $(FLAGS) ./src/Init.cc $(INCLUDE)
	mv Init.o ./build/Init.o

./build/main.o: ./src/main.cc
	$(CC) $(FLAGS) ./src/main.cc $(INCLUDE)
	mv main.o ./build/main.o

clean:
	rm ./build/*.o
	rm ./bin/*
