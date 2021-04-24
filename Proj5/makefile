all: resolution

resolution: resolution.cpp parser.o
	g++ -o resolution -Wall -std=c++11 resolution.cpp parser.o

parser.o: parser.cpp parser.h
	g++ -c -Wall -std=c++11 parser.cpp


clean:
	rm resolution
	rm *.o