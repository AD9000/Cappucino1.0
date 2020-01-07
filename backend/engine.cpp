
#include <iostream>
#include "boards/bitboard.hpp"

int main()
{
    ChessBoard ch = ChessBoard();
    // ch.displayAll();
    ch.generateMoves();
    return 0;
}
