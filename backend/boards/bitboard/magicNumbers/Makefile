CC=g++
MASKDIR=..

all: rfind bfind mfind kfind

.PHONY: findRookMagics
rfind: findRookMagics.cpp $(MASKDIR)/rookMagics.hpp
	$(CC) -o rfind findRookMagics.cpp

.PHONY: findBishopMagics
bfind: findBishopMagics.cpp $(MASKDIR)/bishopMagics.hpp
	$(CC) -o bfind findBishopMagics.cpp

.PHONY: findKnightMasks
mfind: findKnightMasks.cpp
	$(CC) -o mfind findKnightMasks.cpp

.PHONY: findKingMasks
kfind: findKingMasks.cpp
	$(CC) -o kfind findKingMasks.cpp
