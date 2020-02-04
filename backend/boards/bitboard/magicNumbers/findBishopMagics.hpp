#ifndef FINDBISHOPMAGICS_H
#define FINDBISHOPMAGICS_H

#include <cstdint>
#include <vector>
#include "../bitboard.hpp"
using namespace std;

typedef struct _bishopMask
{
    int row;
    int col;
    int ldiag;
    int rdiag;
    bitboard board;
} bishopMask;

vector<bishopMask> generateBishopMasks();
bitboard getBishopLegalMoves(bishopMask, bitboard);
vector<uint64_t> findAllBishopMagicNumbers(vector<bishopMask>);

#endif
