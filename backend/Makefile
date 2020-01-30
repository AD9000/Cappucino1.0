BOARDDIR=boards
BITBOARDDIR=$(BOARDDIR)/bitboard

CC=g++

all: engine

.PHONY: mainengine
engine: engine.o bitboard.o

engine.o: engine.cpp $(BITBOARDDIR)/bitboard.cpp
	$(CC) -c engine.cpp

bitboard.o: $(BITBOARDDIR)/bitboard.cpp $(BITBOARDDIR)/bitboard.hpp
	$(CC) -c $(BITBOARDDIR)/bitboard.hpp $(BITBOARDDIR)/bitboard.cpp

# .PHONY: boards
# $(BOARDDIR)/board.o: $(BOARDDIR)/board.hpp $(BOARDDIR)/bitboard.hpp $(BOARDDIR)/bitboard.cpp
# 	+$(MAKE) -C boards


.PHONY: clean
clean:
	find . -type f -executable -delete
	rm -f *.txt
	rm -f $(BOARDDIR)/*.o
	rm -f *.o
	rm -f *.out
	rm -f engine
	rm -f bfind
	rm -f rfind
