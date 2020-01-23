BOARDDIR=boards

CC=g++

all: rfind bfind engine

.PHONY: findRookMagics
rfind: findRookMagics.cpp $(BOARDDIR)/masks.hpp
	$(CC) -o rfind findRookMagics.cpp

.PHONY: findBishopMagics
bfind: findBishopMagics.cpp $(BOARDDIR)/masks.hpp
	$(CC) -o bfind findBishopMagics.cpp

.PHONY: mainengine
engine:	engine.cpp 
	$(CC) -o engine engine.cpp

.PHONY: boards
$(BOARDDIR)/board.o: $(BOARDDIR)/board.hpp $(BOARDDIR)/bitboard.hpp $(BOARDDIR)/bitboard.cpp
	+$(MAKE) -C boards


.PHONY: clean
clean:
	rm -f $(BOARDDIR)/*.o
	rm -f *.o
	rm -f *.out
	rm -f engine
	rm -f bfind
	rm -f rfind
