all: airportSim

airportSim: main.o readin.o tile.o tiles.o
	g++ -o airportSim main.o readin.o tile.o tiles.o

readin.o: readin.cpp readin.h
	g++ -c readin.cpp

main.o: main.cpp
	g++ -c main.cpp

tile.o: tile.cpp tile.h
	g++ -c tile.cpp

tiles.o: tiles.cpp tiles.h
	g++ -c tiles.cpp

clean: 
	rm *.o airportSim