#ifndef PIECES_HPP
#define PIECES_HPP

#include <unordered_set>
using std::unordered_set;

namespace board
{
enum class Pieces
{
    KING = 'k',
    QUEEN = 'q',
    BISHOP = 'b',
    KNIGHT = 'n',
    ROOK = 'r',
    PAWN = 'p',
};
unordered_set<char> PieceValues({'k', 'q', 'b', 'n', 'r', 'p'});
}; // namespace board

#endif
