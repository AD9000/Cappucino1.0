#include <iostream>
#include <random>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

#include "../../masks.hpp"
#include "findRookMagics.hpp"
#include "../rookMagics.hpp"
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

vector<rookMask> generateRookPossibleMovesMasks()
{
    // For every index on the bitboard
    vector<rookMask> masks(64);
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // Mask
            uint8_t index = row * 8 + col;
            masks[index].row = row;
            masks[index].col = col;
            masks[index].index = index;
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
            masks[index].board = board;
        }
    }

    return masks;
}

uint64_t getLs1bBitboard(bitboard board)
{
    return (board & -board);
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

uint64_t checkMagicNumber(uint64_t number, uint8_t bits)
{
    uint maxIndex = (uint)(pow(2, bits));

    // Check if each blocker fits in the first
    return 0;
}

bitboard getTop(rookMask mask, bitboard blockers)
{
    // search for firstblocker
    bitboard res = 0;
    bitboard colMask = mask.board & columns[mask.col] & blockers;
    int row = mask.row + 1;
    bool firstblocker = false;
    while (row < 8)
    {
        bitboard checker = rows[row] & columns[mask.col];
        if (!firstblocker)
        {
            if (checker & colMask)
            {
                firstblocker = true;
            }
            // Convert to 1 if no blocker
            res |= checker;
        }
        row++;
    }

    return res;
}

bitboard getBottom(rookMask mask, bitboard blockers)
{
    // search for firstblocker
    bitboard res = 0;
    bitboard colMask = mask.board & columns[mask.col] & blockers;
    int row = mask.row - 1;
    bool firstblocker = false;
    while (row >= 0)
    {
        bitboard checker = rows[row] & columns[mask.col];
        if (!firstblocker)
        {
            if (checker & colMask)
            {
                firstblocker = true;
            }
            // Convert to 1 if no blocker
            res |= checker;
        }
        row--;
    }

    return res;
}

bitboard getLegalRowBitboard(rookMask mask, bitboard blockers)
{
    bitboard andRes = mask.board & blockers;
    // bitboard topCol = getTopColBoard(andRes, row, col);
    bitboard rowBitBoard = andRes;

    return getTop(mask, blockers) | getBottom(mask, blockers);
}

bitboard getRight(rookMask mask, bitboard blockers)
{
    // search for firstblocker
    bitboard res = 0;
    bitboard rowMask = mask.board & rows[mask.row] & blockers;
    int col = mask.col - 1;
    bool firstblocker = false;
    while (col >= 0)
    {
        bitboard checker = rows[mask.row] & columns[col];
        if (!firstblocker)
        {
            if (checker & rowMask)
            {
                firstblocker = true;
            }
            // Convert to 1 if no blocker
            res |= checker;
        }
        col--;
    }

    return res;
}

bitboard getLeft(rookMask mask, bitboard blockers)
{
    // search for firstblocker
    bitboard res = 0;
    bitboard rowMask = mask.board & rows[mask.row] & blockers;
    int col = mask.col + 1;
    bool firstblocker = false;
    while (col < 8)
    {
        bitboard checker = rows[mask.row] & columns[col];
        if (!firstblocker)
        {
            if (checker & rowMask)
            {
                firstblocker = true;
            }
            // Convert to 1 if no blocker
            res |= checker;
        }
        col++;
    }

    return res;
}

bitboard getLegalColumnBitboard(rookMask mask, bitboard blockers)
{
    return getLeft(mask, blockers) | getRight(mask, blockers);
}

bitboard generateLegalMoveBitboard(rookMask mask, bitboard blockers)
{
    return ((getLegalRowBitboard(mask, blockers) | getLegalColumnBitboard(mask, blockers)));
}

void generateAllPossibleRookMoves(uint64_t mask)
{
}

void generateRookMagics(unordered_map<uint16_t, bitboard> &rookMagics)
{
    vector<rookMask> masks = generateRookPossibleMovesMasks();

    for (rookMask mask : masks)
    {
        // Generating all possible blocker variations for the
        unordered_set<bitboard> variations;
        generateBlockerVariations(50, 0, variations);
        // vector<bitboard> possibleMoves = generateAllPossibleRookMoves(possibleMoves, mask);
    }

    for (int8_t i = 0; i < 64; i++)
    {
        displayBoard(masks[i].board);
    }
}

template <typename T>
void printUnorderedSet(unordered_set<T> variations)
{
    cout << variations.size() << endl;
    for (auto itr = variations.begin(); itr != variations.end(); itr++)
    {
        cout << (*itr) << endl;
        // displayBoard(*itr);
    }
}

bitboard findMagicNumber(bitboard rookMask)
{
    uint64_t x = bitboardMax >> 5;
    uint64_t counter = 0;
    vector<uint16_t> indices;
    unordered_set<bitboard> variations;
    generateBlockerVariations(rookMask, 0, variations);
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
            if (generated.size() % 10000000000UL == 0)
            {
                printf("%lu, %lu\n", hasher, generated.size());
            }
        }
        unordered_set<uint16_t> indices;
        // cout << "len: " << indices.size() << endl;
        for (bitboard variation : variations)
        {
            uint16_t index = (hasher * variation) >> 50;
            if (!indices.insert(index).second)
            {
                cout << "Broke at : " << indices.size() << endl;
                break;
            }
        }
        if (indices.size() == variations.size())
        {
            // cout << indices.size() << endl;
            // cout << variations.size() << endl;
            // cout << "Start" << endl;
            vector<uint16_t> cp;
            cp.insert(cp.end(), indices.begin(), indices.end());
            for (uint16_t index : cp)
            {
                cout << "index: " << index << endl;
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
        return hasher;
    }
    else
    {
        return 0;
    }
}

void testMagicNumber(bitboard mask, bitboard magic)
{
    unordered_set<bitboard> variations;
    generateBlockerVariations(mask, 0, variations);

    unordered_set<int> indices;
    cout << variations.size() << endl;

    for (bitboard variation : variations)
    {
        int index = (variation * magic) >> 48;
        cout << index << endl;
        indices.insert(index);
    }

    cout << indices.size() << endl;
}

vector<uint64_t> findAllRookMagicNumbers(vector<rookMask> masks)
{
    vector<uint64_t> magicNumbers(64, 0);
    ofstream myfile;
    myfile.open("rookMagics.txt");
    myfile << "bitboard rookMagics = {";
    for (int i = 0; i < masks.size(); i++)
    {
        bitboard magicNumber = findMagicNumber(masks[i].board);
        magicNumbers[i] = magicNumber;

        if (magicNumber == 0)
        {
            cout << "oof" << endl;
            break;
        }

        myfile << "0x" << hex << magicNumber << "ULL, ";
    }
    myfile.close();
    return magicNumbers;
}

int main()
{
    // vector<rookMask> masks = generateRookPossibleMovesMasks();
    // displayBoard(masks[50].board);
    // unordered_set<bitboard> variations;
    // generateBlockerVariations(masks[50].board, 0, variations);
    // for (auto variation : variations)
    // {
    //     cout << "For variation: " << endl;
    //     displayBoard(variation);
    //     cout << "Legal: " << endl;
    //     displayBoard(generateLegalMoveBitboard(masks[50], variation));
    // }
    // findAllRookMagicNumbers(generateRookPossibleMovesMasks());
    vector<vector<bitboard>> res;
    vector<rookMask> masks = generateRookPossibleMovesMasks();
    int i = 0;
    for (rookMask mask : masks)
    {
        vector<bitboard> posRes;
        bitboard hasher = RookMagics::rookMagics[i];
        unordered_set<bitboard> variations;
        generateBlockerVariations(mask.board, 0, variations);
        for (bitboard variation : variations)
        {
            bitboard l = generateLegalMoveBitboard(mask, variation);
            int index = (variation * hasher) >> 50;
            if (index + 1 > posRes.size())
            {
                posRes.resize(index + 1);
            }
            posRes[index] = l;
        }
        // cout << posRes.size() << endl;
        res.push_back(posRes);
        i++;
    }
    // cout << "Res: " << res.size() << endl;

    for (bitboard b : res[0])
    {
        cout << b << endl;
    }

    // ofstream magic;
    ofstream myfile;
    // magic.open("magic.txt");
    myfile.open("rookHash.txt");
    myfile << "bitboard rookLegals[][] = { ";
    for (auto pos : res)
    {
        myfile << "{";
        for (bitboard b : pos)
        {
            myfile << "0x" << hex << b << "ULL, ";
        }
        myfile << "}, " << endl;
    }
    myfile.close();

    return 0;
}
