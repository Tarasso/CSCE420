all: BlocksworldAstar

BlocksworldAstar: BlocksworldAstar.cpp HelperLib.o State.o Node.o 
	g++ -o BlocksworldAstar -Wall -std=c++11 BlocksworldAstar.cpp State.o Node.o HelperLib.o -g

HelperLib.o: HelperLib.cpp HelperLib.h
	g++ -c -Wall -std=c++11 HelperLib.cpp -g

State.o: State.cpp State.h HelperLib.h
	g++ -c -Wall -std=c++11 State.cpp -g

Node.o: Node.cpp Node.h State.h
	g++ -c -Wall -std=c++11 Node.cpp -g



run:
	./BlocksworldAstar $(FILE)

valgrind:
	valgrind --leak-check=full ./BlocksworldAstar $(FILE) 

clean:
	rm *.o