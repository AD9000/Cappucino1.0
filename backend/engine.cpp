#include <iostream>

#include "engine.hpp"
using namespace std;

void engineMove(ChessBoard &board)
{
    cout << "Engine Moved!" << endl;
    board.endTurn();
}
