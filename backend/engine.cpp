
#include <iostream>
#include "boards/bitboard/bitboard.hpp"
using namespace std;
using namespace masks;

int main()
{
    // Create a chess board
    ChessBoard board = ChessBoard();

    // display it
    board.displayAll();

    return 0;
}
