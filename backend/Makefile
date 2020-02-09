BOARDDIR=boards
BITBOARDDIR=$(BOARDDIR)/bitboard
PIECESDIR=$(BITBOARDDIR)/pieces

CC=g++

all: game

.PHONY: playgame
game: game.o engine.o bitboard.o helper.o

game.o: game.cpp engine.o bitboard.o $(PIECESDIR)/pieces.hpp
	$(CC) -c game.cpp

.PHONY: mainengine
engine: engine.o

engine.o: engine.cpp 
	$(CC) -c engine.cpp

bitboard.o: $(BITBOARDDIR)/bitboard.cpp $(BITBOARDDIR)/bitboard.hpp $(PIECESDIR)/pieces.hpp helper.o
	$(CC) -c $(BITBOARDDIR)/bitboard.cpp 

helper.o: $(BITBOARDDIR)/helper.cpp $(BITBOARDDIR)/helper.hpp
	$(CC) -c $(BITBOARDDIR)/helper.hpp $(BITBOARDDIR)/helper.cpp


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
	rm -f *.hpp.gch
