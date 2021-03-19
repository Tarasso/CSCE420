all: sammys

sammys: sammys.cpp NatDed.o parser.o
	g++ -o sammys -Wall -std=c++11 sammys.cpp NatDed.o parser.o

parser.o: parser.cpp parser.h
	g++ -c -Wall -std=c++11 parser.cpp

NatDed.o: NatDed.cpp NatDed.h
	g++ -c -Wall -std=c++11 NatDed.cpp

run:
	./sammys

clean:
	rm sammys
	rm *.o