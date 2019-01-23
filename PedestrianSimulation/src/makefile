CC=g++ -ansi -pedantic -std=c++11

all: PedestrianSimulation.o Floor.o Builder.o Cotainers.o
	$(CC) PedestrianSimulation.o Floor.o Builder.o Cotainers.o -o testoo

Cotainers.o: Cotainers.cpp Cotainers.h 
	$(CC) Cotainers.cpp -c -o Cotainers.o

Builder.o: Builder.cpp Builder.h
	$(CC) Builder.cpp -c -o Builder.o

Floor.o: Floor.cpp Floor.h Builder.h Cotainers.h
	$(CC) Floor.cpp -c -o Floor.o

PedestrianSimulation.o: PedestrianSimulation.cpp Floor.h Builder.h Cotainers.h
	$(CC) PedestrianSimulation.cpp -c -o PedestrianSimulation.o

clean:
	rm -f *.o testoo
	rm -f *.obj
