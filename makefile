all: BlocksworldBFS

BlocksworldBFS: BlocksworldBFS.cpp
	g++ -o Proj1 -std=c++11 BlocksworldBFS.cpp


run: ./Proj1