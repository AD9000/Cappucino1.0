#ifndef FINDROOKMAGICS_H
#define FINDROOKMAGICS_H

#include <cstdint>
#include <vector>
#include "boards/bitboard.hpp"
using namespace std;

typedef struct _rookMask
{
    int row;
    int col;
    int index;
    bitboard board;
} rookMask;

vector<rookMask> generateRookPossibleMovesMasks();
bitboard generateLegalMoveBitboard(rookMask, bitboard);
vector<uint64_t> findAllRookMagicNumbers(vector<rookMask> masks);

#endif
