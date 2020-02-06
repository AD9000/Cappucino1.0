CC=g++
MASKDIR=..

all: rfind bfind

.PHONY: findRookMagics
rfind: findRookMagics.cpp $(MASKDIR)/rookMagics.hpp
	$(CC) -o rfind findRookMagics.cpp

.PHONY: findBishopMagics
bfind: findBishopMagics.cpp $(MASKDIR)/bishopMagics.hpp
	$(CC) -o bfind findBishopMagics.cpp
