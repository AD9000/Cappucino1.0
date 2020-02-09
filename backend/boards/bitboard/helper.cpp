#include <cstdint>
#include <iostream>
#include "helper.hpp"
using namespace masks;
using namespace std;

int findLDiag(int row, int col)
{
    return col + (7 - row);
}

int findRDiag(int row, int col)
{
    return 14 - row - col;
}

bitboard generateBishopMask(uint8_t row, uint8_t col)
{
    bitboard position = rows[row] & columns[col];
    // cout << "Position, ldiag and rdiag" << endl;
    // displayBoard(position);
    int ldiag = findLDiag(row, col);
    int rdiag = findRDiag(row, col);
    // cout << "Row, col, ldiag, rdiag: " << row + 0 << " " << col + 0 << " " << ldiag + 0 << " " << rdiag + 0 << endl;
    // displayBoard(ldiags[ldiag]);
    // displayBoard(rdiags[rdiag]);
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

void displayBoard(bitboard board)
{
    bitboard mask = 1ULL << 63;
    for (int i = 1; i <= 64; i++)
    {
        if ((mask >> (i - 1)) & board)
        {
            printf("#");
        }
        else
        {
            printf(".");
        }

        if (i % 8 == 0)
        {
            printf("\n");
        }
    }
}
