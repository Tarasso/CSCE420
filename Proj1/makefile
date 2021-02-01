all: BlocksworldBFS

BlocksworldBFS: BlocksworldBFS.cpp State.o
	g++ -o a.out -std=c++11 BlocksworldBFS.cpp State.o -g

State.o: State.cpp State.h
	g++ -c -std=c++11 State.cpp -g

run:
	./a.out $(FILE)