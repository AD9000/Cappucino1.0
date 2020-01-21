#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <fstream>
#include <bitset>

#include "boards/masks.hpp"
using namespace std;
using namespace masks;

typedef struct _bishopMask
{
    int row;
    int col;
    int ldiag;
    int rdiag;
    bitboard board;
} bishopMask;

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

vector<bishopMask> generateBishopMasks()
{
    // For every index on the bitboard
    vector<bishopMask> masks(64);
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int index = row * 8 + col;
            bitboard position = rows[row] & columns[col];
            masks[index].row = row;
            masks[index].col = col;
            masks[index].ldiag = findLDiag(position);
            masks[index].rdiag = findRDiag(position);
            bitboard board = ldiags[masks[index].ldiag] ^ rdiags[masks[index].rdiag];
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
            masks[index].board = board;
        }
    }

    return masks;
}

template <typename T>
void printUnorderedSet(unordered_set<T> variations)
{
    cout << variations.size() << endl;
    for (auto itr = variations.begin(); itr != variations.end(); itr++)
    {
        // cout << (*itr) << endl;
        displayBoard(*itr);
    }
}

// Generate all possible blocker boards for given bitboard, at given depth
void generateBlockerVariations(bitboard board, uint16_t startIndex, unordered_set<bitboard> &variations)
{
    for (uint16_t i = startIndex; i < 64; i++)
    {
        bitboard checker = (1ULL << i);
        if ((checker & board) && board)
        {
            // printf("index: %d\n", i);
            bitboard newBoard = board & ~checker;
            // displayBoard(newBoard);
            variations.insert(board);
            variations.insert(newBoard);
            generateBlockerVariations(board, i + 1, variations);
            generateBlockerVariations(newBoard, i, variations);
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

bitboard findMagicNumber(bitboard bishopMask)
{
    uint64_t x = bitboardMax >> 5;
    uint64_t counter = 0;
    unordered_set<bitboard> variations;
    generateBlockerVariations(bishopMask, 0, variations);
    // For each possible variation for a rook position,
    // Test number
    unordered_set<uint64_t> generated;
    uint64_t hasher;
    bool check = false;
    while (true)
    {
        hasher = generateRandomNumber();
        if (generated.find(hasher) != generated.end())
        {
            printf("%lu, %lu\n", hasher, generated.size());
            continue;
        }
        else
        {
            generated.insert(hasher);
            if (generated.size() % 10000000000 == 0)
            {
                printf("%lu, %lu\n", hasher, generated.size());
            }
        }
        unordered_set<uint16_t> indices;
        for (bitboard variation : variations)
        {
            uint16_t index = (hasher * variation) >> 51;
            if (indices.find(index) != indices.end())
            {
                break;
            }
            else
            {
                indices.insert(index);
            }
        }
        if (indices.size() == variations.size())
        {
            cout << indices.size() << endl;
            cout << variations.size() << endl;
            cout << "Start" << endl;
            for (uint16_t index : indices)
            {
                cout << index << endl;
            }
            check = true;
            break;
        }
        else
        {
            printf("Tested: %lu, Size of test: %lu\n", hasher, indices.size());
        }
    }
    if (check)
    {
        // ofstream myfile;
        // myfile.open("example.txt");
        // myfile << hasher << endl;
        // myfile << "Writing this to a file.\n";
        // myfile << variations.size() << endl;
        // for (auto itr = variations.begin(); itr != variations.end(); itr++)
        // {
        //     myfile << (*itr) << endl;
        //     // displayBoard(*itr);
        // }

        // myfile.close();
    }

    return hasher;
}

void findAllBishopMagicNumbers(vector<bishopMask> masks)
{
    uint16_t magicNumbers[64] = {0};
    ofstream myfile;
    myfile.open("bishopMagics.txt");
    for (int i = 0; i < masks.size(); i++)
    {
        bitboard magicNumber = findMagicNumber(masks[i].board);
        magicNumbers[i] = magicNumber;

        myfile << hex << magicNumber << endl;
    }
    myfile.close();
}

bitboard generateTopLDiag(bishopMask mask, bitboard andres)
{
    int maskIndex = mask.row * 8 + mask.col;

    bitset<64> ldiag = ldiags[mask.ldiag];
    bool firstBlocker = false;
    int row = mask.row - 1;
    int col = mask.col - 1;
    int lastBitIndex = row * 8 + col;
    while (row >= 0 && col >= 0)
    {
        bitboard adder = (1ULL << lastBitIndex);
        if (adder & andres > 0)
        {
            firstBlocker = true;
        }

        if (firstBlocker)
        {
            // set to 0
            andres &= ~adder;
        }
        else
        {
            andres |= adder;
        }
        row--;
        col--;
        lastBitIndex = row * 8 + col;
    }
    return andres;
}

bitboard generateLegalLDiag(bishopMask mask, bitboard andres, bitboard blockers)
{
    bitboard ldiag = ldiags[mask.ldiag];

    int maskIndex = mask.row * 8 + mask.col;
    bitboard ldiagMask = (mask.board & ldiags[mask.ldiag]) & blockers;
    bitset<64> set = ldiags[mask.ldiag];
    // bitboard adder = ldiags[]

    // cout << "Start: maskindex: " << maskIndex << endl;

    // displayBoard(blockers);
    // displayBoard(ldiagMask);

    // // For every element until the maskIndex
    // int firstBlocker = maskIndex;
    // int index = set._Find_first();
    // while (index < 64)
    // {
    //     // test the index
    //     if (index == maskIndex)
    //     {
    //         break;
    //     }

    //     // If there was a firstBlocker previously, set it to 0
    //     if (firstBlocker != maskIndex)
    //     {
    //         ldiagMask &= ~(1ULL << firstBlocker);
    //     }
    //     else {
    //         // New blocker only if there exists a 1. otherwise remove it
    //         firstBlocker = index;
    //     }

    //     // next
    //     index = set._Find_next(index);
    // }

    // // If never changed, add in corner
    // if (firstBlocker == maskIndex)
    // {
    //     ldiagMask |= 1;
    // }
    // else {
    //     // Otherwise add ones between
    // }

    bitset<64> t2 = ldiagMask;
    int lastBitIndex = t2._Find_first();
    int firstBlocker = maskIndex;
    int row = lastBitIndex / 8;
    int col = mask.col % 8;
    while (lastBitIndex < (63 - maskIndex))
    {
        // 1 at index
        firstBlocker = lastBitIndex;
        lastBitIndex = t2._Find_next(lastBitIndex);
    }

    // cout << "First blocker: " << firstBlocker << " " << maskIndex << endl;
    // displayBoard(ldiagMask);

    if (firstBlocker == maskIndex)
    {
        bitset<64> temp = ldiags[mask.ldiag];
        ldiagMask = mask.board | (1 << temp._Find_first());
    }
    else
    {
        // Set everything below firstblocker to 0 and above to 1
        // cout << "hmmm" << endl;
        bitset<64> temp = ldiags[mask.ldiag];
        int temp2 = 63 - temp._Find_first();
        row = temp2 / 8;
        col = temp2 % 8;
        int bRow = (63 - firstBlocker) / 8;
        int bCol = (63 - firstBlocker) % 8;
        bitboard adder = 0;
        // cout << "hmmm: " << row << " " << bRow << endl;
        while (row > mask.row && col > mask.col)
        {
            // cout << "hmmm" << row << " " << bRow << endl;
            // displayBoard((1ULL << lastBitIndex));
            if (row <= bRow)
            {
                // Make 1
                int index = 63 - (row * 8 + col);
                adder |= (1ULL << index);
            }
            row--;
            col--;
        }
        // cout << "adder" << endl;
        // displayBoard(adder);
        ldiagMask = adder;
    }

    // cout << "Final left diag: " << endl;
    // displayBoard(blockers);
    // displayBoard(ldiagMask);

    return ldiagMask;
    // return generateTopLDiag(mask, ldiagMask);
}

bitboard getBishopLegalMoves(bishopMask mask, bitboard blockers)
{
    bitboard andres = mask.board & blockers;
    return generateLegalLDiag(mask, andres, blockers);
}

int main()
{
    vector<bishopMask> masks = generateBishopMasks();
    unordered_set<bitboard> variations;
    generateBlockerVariations(masks[0].board, 0, variations);
    for (auto variation : variations)
    {
        displayBoard(getBishopLegalMoves(masks[0], variation));
        displayBoard(variation);
        // break;
    }
    // findAllBishopMagicNumbers(masks);
    // printUnorderedSet(variations);
    // for (auto i = masks.begin(); i != masks.end(); i++)
    // {
    //     displayBoard(*i);
    // }
    return 0;
}
