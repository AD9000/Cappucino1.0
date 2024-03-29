#include <cstdint>
#include "../masks.hpp"
using namespace masks;

int findLDiag(bitboard position)
{
    int len = sizeof(ldiags) / sizeof(bitboard);
    for (int i = 0; i < len; i++)
    {
        if (position & ldiags[i])
        {
            return i;
        }
    }
}

int findRDiag(bitboard position)
{
    int len = sizeof(rdiags) / sizeof(bitboard);
    for (int i = 0; i < len; i++)
    {
        if (position & rdiags[i])
        {
            return i;
        }
    }
}

bitboard generateBishopMask(uint8_t row, uint8_t col)
{
    bitboard position = rows[row] & columns[col];
    int ldiag = findLDiag(position);
    int rdiag = findRDiag(position);
    bitboard board = ldiags[ldiag] ^ rdiags[rdiag];
    if (row != 0)
    {
        board &= ~rows[0];
    }
    if (row != 7)
    {
        board &= ~rows[7];
    }
    if (col != 0)
    {
        board &= ~columns[0];
    }
    if (col != 7)
    {
        board &= ~columns[7];
    }
    return board;
}

bitboard generateRookMask(uint8_t row, uint8_t col)
{
    bitboard board = rows[row] ^ columns[col];
    // Assuming that the rook is not on the edge, remove edges
    if (row && row != 7)
    {
        board &= ~rows[0];
        board &= ~rows[7];
    }
    else if (row)
    {
        board &= ~rows[0];
    }
    else
    {
        board &= ~rows[7];
    }

    if (col && col != 7)
    {
        board &= ~columns[0];
        board &= ~columns[7];
    }
    else if (col)
    {
        board &= ~columns[0];
    }
    else
    {
        board &= ~columns[7];
    }
    return board;
}
