CC = g++
FLAGS = -c
INCLUDE = -I ./include
OBJECTS = ./build/*.o

readers_writers: ./build/RWlock.o ./build/main.o
	$(CC) -o $@ $(OBJECTS) -lpthread 
	mv readers_writers ./bin/readers_writers

./build/RWlock.o: ./src/RWlock.cc ./include/RWlock.h
	$(CC) $(FLAGS) ./src/RWlock.cc $(INCLUDE)
	mv RWlock.o ./build/RWlock.o

./build/main.o: ./src/main.cc
	$(CC) $(FLAGS) ./src/main.cc $(INCLUDE)
	mv main.o ./build/main.o

clean:
	rm ./build/*.o
	rm ./bin/*
