#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <unordered_set>
using namespace std;

namespace board
{
enum class PieceType
{
    KING = 'k',
    QUEEN = 'q',
    BISHOP = 'b',
    KNIGHT = 'n',
    ROOK = 'r',
    PAWN = 'p',
};

typedef struct _move
{
    PieceType piece;
    pair<int8_t, int8_t> startingPos;
    pair<int8_t, int8_t> finalPos;
    _move()
    {
        piece = PieceType::PAWN,
        startingPos = make_pair(-1, -1);
        finalPos = make_pair(-1, -1);
    }
    _move(PieceType p, char sFile, char sRank, char fFile, char fRank)
    {
        piece = p;
        // cout << "startingPos: (" << sRank - '1' << ", " << 7 - (sFile - 'a') << ")" << endl;
        startingPos = make_pair(sRank - '1', 7 - (sFile - 'a'));
        finalPos = make_pair(fRank - '1', 7 - (fFile - 'a'));
    }
} Move;

}; // namespace board

#endif
