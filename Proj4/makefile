all: DPLL

DPLL: DPLL.cpp parser.o
	g++ -o dpll -Wall -std=c++11 DPLL.cpp parser.o

parser.o: parser.cpp parser.h
	g++ -c -Wall -std=c++11 parser.cpp

run:
	./dpll $(KB)

clean:
	rm dpll
	rm *.o