#include <iostream>
#include <vector>

#include "boards/masks.hpp"
using namespace std;
using namespace masks;

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
    printf("\n");
}

bitboard findLDiag(bitboard position)
{
    for (bitboard ldiag : ldiags)
    {
        if (position & ldiag)
        {
            return ldiag;
        }
    }
}

bitboard findRDiag(bitboard position)
{
    for (bitboard rdiag : rdiags)
    {
        if (position & rdiag)
        {
            return rdiag;
        }
    }
}

vector<bitboard> generateBishopMasks()
{
    // For every index on the bitboard
    vector<bitboard> masks(64);
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int index = row * 8 + col;
            bitboard position = rows[row] & columns[col];
            masks[index] = findLDiag(position) ^ findRDiag(position);
            if (row != 0)
            {
                masks[index] &= ~rows[0];
            }
            if (row != 7)
            {
                masks[index] &= ~rows[7];
            }
            if (col != 0)
            {
                masks[index] &= ~columns[0];
            }
            if (col != 7)
            {
                masks[index] &= ~columns[7];
            }
        }
    }

    return masks;
}

int main()
{
    vector<bitboard> masks = generateBishopMasks();
    for (auto i = masks.begin(); i != masks.end(); i++)
    {
        displayBoard(*i);
    }
    return 0;
}
