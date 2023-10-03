CC = g++
CFLAGS = -std=c++11 -Wall -Werror -pedantic
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: NBody

NBody: NBody.o CelestialBody.o Universe.o
	$(CC) $(CFLAGS) -o NBody NBody.o CelestialBody.o Universe.o $(SFMLFLAGS)
NBody.o: NBody.cpp CelestialBody.hpp Universe.hpp
	$(CC) $(CFLAGS) -c NBody.cpp -o NBody.o 
CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c CelestialBody.cpp -o CelestialBody.o
Universe.o: Universe.cpp Universe.hpp
	$(CC) $(CFLAGS) -c Universe.cpp -o Universe.o

clean:
	rm NBody *.o

