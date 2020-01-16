#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <bitset>
#include <unordered_set>
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

uint64_t *generateRookPossibleMovesMasks()
{
    // For every index on the bitboard
    uint64_t *masks = (uint64_t *)malloc(64 * sizeof(uint64_t));
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // Mask
            uint8_t index = row * 8 + col;
            masks[index] = rows[row] ^ columns[col];
            // Assuming that the rook is not on the edge, remove edges
            if (row && row != 7)
            {
                masks[index] &= ~rows[0];
                masks[index] &= ~rows[7];
            }
            else if (row)
            {
                masks[index] &= ~rows[0];
            }
            else
            {
                masks[index] &= ~rows[7];
            }

            if (col && col != 7)
            {
                masks[index] &= ~columns[0];
                masks[index] &= ~columns[7];
            }
            else if (col)
            {
                masks[index] &= ~columns[0];
            }
            else
            {
                masks[index] &= ~columns[7];
            }
        }
    }

    return masks;
}

uint64_t getLs1bBitboard(bitboard board)
{
    return (board & -board);
}

// Generate all possible blocker boards for given bitboard, at given depth
void generateBlockerVariations(bitboard board, uint8_t startIndex, unordered_set<uint64_t> variations)
{
    for (uint8_t i = startIndex; i < 64; i++)
    {
        uint64_t checker = (1 << i);
        if (checker & board)
        {
            variations.insert(board);
            variations.insert(board & ~checker);
            generateBlockerVariations(board, startIndex, variations);
        }
    }
}

uint64_t generateRandomNumber()
{
    random_device dev;
    mt19937_64 rng(dev());
    uniform_int_distribution<mt19937_64::result_type> dist(1, UINT64_MAX);

    return dist(rng);
}

uint64_t checkMagicNumber(uint64_t number, uint8_t bits)
{
    uint maxIndex = (uint)(pow(2, bits));

    // Check if each blocker fits in the first
    return 0;
}

void generateRookMagics()
{
    // displayBoard(!rows[0]);
    uint64_t *masks = generateRookPossibleMovesMasks();

    for (int8_t i = 0; i < 64; i++)
    {
        displayBoard(masks[i]);
    }
}

int main()
{
    // printf("The numbers are:\n");
    // generateRookMagics();
    unordered_set<uint64_t> variations;
    generateBlockerVariations(50, 0, variations);
    cout << variations.size() << endl;
    for (auto itr = variations.begin(); itr != variations.end(); itr++)
        cout << (*itr) << endl;
    return 0;
}

// int main()
// {
//     // printf("The numbers are:\n");
//     // generateRookMagics();
//     uint64_t x = 283242394;
//     displayBoard(x);
//     asm("bsf &x x");
//     return 0;
// }
