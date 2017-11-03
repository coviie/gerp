###########################################################################
##                        Makefile for (Gerp)                            ##
###########################################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g3

gerp: TreeTraversal.o DirNode.o FSTree.o gerp.o Indexer.o Trie.o 
	${CXX} ${LDFLAGS} -o gerp TreeTraversal.o DirNode.o FSTree.o gerp.o \
					Indexer.o Trie.o stringProcessing.o


Trie.o: 	Key.h Trie.h Trie.cpp
Indexer.o: 	Indexer.h Indexer.cpp TreeTraversal.h stringProcessing.h \
		Trie.h Key.h
stringProcessing.o: stringProcessing.h stringProcessing.cpp
TreeTraversal.o: TreeTraversal.h TreeTraversal.cpp
HashTable.o: Key.h HashTable.h HashTable.cpp
gerp.o: gerp.cpp DirNode.h FSTree.h TreeTraversal.h 

clean:
	rm -rf gerp *.o *.dSYM
				