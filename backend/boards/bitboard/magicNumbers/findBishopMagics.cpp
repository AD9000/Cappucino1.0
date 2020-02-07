#include <iostream>
#include <unordered_set>
#include <random>
#include <fstream>
#include <bitset>

#include "../masks.hpp"
#include "findBishopMagics.hpp"
#include "../pieces/bishopMagics.hpp"
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
    // For each possible variation for a bishop position,
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

vector<uint64_t> findAllBishopMagicNumbers(vector<bishopMask> masks)
{
    vector<uint64_t> magicNumbers(64, 0);
    ofstream myfile;
    myfile.open("bishopMagics.txt");
    myfile << "bitboard bishopMagics[] = { ";
    for (int i = 0; i < masks.size(); i++)
    {
        uint64_t magicNumber = findMagicNumber(masks[i].board);
        magicNumbers[i] = magicNumber;

        myfile << "0x" << hex << magicNumber << "ULL, ";
    }
    myfile.close();

    return magicNumbers;
}

bitboard generateTopLDiag(bishopMask mask, bitboard andres, bitboard blockers)
{

    int maskIndex = mask.row * 8 + mask.col;

    bitset<64> ldiag = ldiags[mask.ldiag];
    bool firstBlocker = false;
    int row = mask.row + 1;
    int col = mask.col + 1;
    // displayBoard(rows[mask.row] & columns[mask.col]);
    while (row < 8 && col < 8)
    {
        // cout << "row: " << row << ", col: " << col << endl;
        bitboard adder = rows[row] & columns[col];
        if ((adder & blockers) > 0 && !firstBlocker)
        {
            firstBlocker = true;
            andres |= adder;
            row++;
            col++;
            continue;
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
        row++;
        col++;
    }

    return andres;
}

bitboard generateLegalLDiag(bishopMask mask, bitboard blockers)
{
    bitboard andres = mask.board & ldiags[mask.ldiag];
    int maskIndex = mask.row * 8 + mask.col;

    bitset<64> ldiag = ldiags[mask.ldiag];
    bool firstBlocker = false;
    int row = mask.row - 1;
    int col = mask.col - 1;
    // displayBoard(rows[mask.row] & columns[mask.col]);
    while (row >= 0 && col >= 0)
    {
        // cout << "row: " << row << ", col: " << col << endl;
        bitboard adder = rows[row] & columns[col];
        if ((adder & blockers) > 0 && !firstBlocker)
        {
            firstBlocker = true;
            andres |= adder;
            row--;
            col--;
            continue;
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
    }
    // return ldiagMask;
    return generateTopLDiag(mask, andres, blockers);
}

bitboard generateTopRDiag(bishopMask mask, bitboard andres, bitboard blockers)
{
    // std::cout << "start: " << endl;
    // displayBoard(andres);
    int maskIndex = mask.row * 8 + mask.col;
    bitset<64> rdiag = rdiags[mask.rdiag];
    bool firstBlocker = false;
    int row = mask.row + 1;
    int col = mask.col - 1;
    // cout << "row: " << row << ", col: " << col << endl;
    // displayBoard(rows[mask.row] & columns[mask.col]);
    while (row < 8 && col >= 0)
    {
        // cout << "row: " << row << ", col: " << col << endl;
        bitboard adder = rows[row] & columns[col];
        if ((adder & blockers) > 0 && !firstBlocker)
        {
            firstBlocker = true;
            andres |= adder;
            row++;
            col--;
            continue;
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
        row++;
        col--;
    }

    return andres;
}

bitboard getLegalRDiag(bishopMask mask, bitboard blockers)
{
    bitboard andres = mask.board & rdiags[mask.rdiag];
    // std::cout << "start: " << endl;
    // displayBoard(andres);
    int maskIndex = mask.row * 8 + mask.col;
    bitset<64> rdiag = rdiags[mask.rdiag];
    bool firstBlocker = false;
    int row = mask.row - 1;
    int col = mask.col + 1;

    // displayBoard(andres);
    // cout << "row: " << row << ", col: " << col << endl;
    // displayBoard(rows[mask.row] & columns[mask.col]);
    while (row >= 0 && col < 8)
    {
        // cout << "row: " << row << ", col: " << col << endl;
        bitboard adder = rows[row] & columns[col];
        // cout << "Adding..." << endl;
        // displayBoard(adder);
        if ((adder & blockers) > 0 && !firstBlocker)
        {
            firstBlocker = true;
            andres |= adder;
            row--;
            col++;
            continue;
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
        col++;
    }
    // cout << "First blocker: " << firstBlocker << endl;
    // displayBoard(andres);
    return generateTopRDiag(mask, andres, blockers);
}

bitboard getBishopLegalMoves(bishopMask mask, bitboard blockers)
{
    return generateLegalLDiag(mask, blockers) | getLegalRDiag(mask, blockers);
}

int main()
{
    vector<vector<bitboard>> res;
    vector<bishopMask> masks = generateBishopMasks();
    int i = 0;
    for (bishopMask mask : masks)
    {
        vector<bitboard> posRes;
        bitboard hasher = BishopMagics::bishopMagics[i];
        unordered_set<bitboard> variations;
        generateBlockerVariations(mask.board, 0, variations);
        for (bitboard variation : variations)
        {
            bitboard l = getBishopLegalMoves(mask, variation);
            int index = (variation * hasher) >> 51;
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

    ofstream myfile;
    myfile.open("bishopHash.txt");
    myfile << "bitboard bishopLegals[][] = { ";
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
    // vector<bishopMask> masks = generateBishopMasks();
    // for (auto mask : masks)
    // {
    //     unordered_set<bitboard> variations;
    //     generateBlockerVariations(mask.board, 0, variations);
    //     for (auto variation : variations)
    //     {
    //         displayBoard(mask.board);
    //         displayBoard(getBishopLegalMoves(mask, variation));
    //         displayBoard(variation);
    //         // break;
    //     }
    // }

    // unordered_set<bitboard> variations;
    // generateBlockerVariations(masks[28].board, 0, variations);
    // int i = 0;
    // for (auto variation : variations)
    // {
    //     cout << "Mask: " << endl;
    //     displayBoard(masks[28].board);
    //     cout << "Legal: " << endl;
    //     displayBoard(getBishopLegalMoves(masks[28], variation));
    //     cout << "variation: " << endl;
    //     displayBoard(variation);
    //     // if (i == 3)
    //     // {
    //     //     break;
    //     // }
    //     // i++;
    //     // break;
    // }
    // findAllBishopMagicNumbers(masks);
    // printUnorderedSet(variations);
    // for (auto i = masks.begin(); i != masks.end(); i++)
    // {
    //     displayBoard(*i);
    // }
    return 0;
}
