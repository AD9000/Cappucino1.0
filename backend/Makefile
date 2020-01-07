BOARDDIR=boards

CC=g++

engine:	engine.o $(BOARDDIR)/board.o

engine.o: engine.cpp 
	g++ -c engine.cpp

$(BOARDDIR)/board.o: $(BOARDDIR)/board.hpp $(BOARDDIR)/bitboard.hpp $(BOARDDIR)/bitboard.cpp
	+$(MAKE) -C boards

clean:
	rm $(BOARDDIR)/board.o
	rm engine.o
