all: BlocksworldBFS

BlocksworldBFS: BlocksworldBFS.cpp State.o Node.o
	g++ -o BlocksworldBFS -std=c++11 BlocksworldBFS.cpp State.o Node.o -g

State.o: State.cpp State.h
	g++ -c -std=c++11 State.cpp -g

Node.o: Node.cpp Node.h State.h
	g++ -c -std=c++11 Node.cpp -g

run:
	./BlocksworldBFS $(FILE)

valgrind:
	valgrind ./BlocksworldBFS $(FILE) 

clean:
	rm *.out
	rm *.o