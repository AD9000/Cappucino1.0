#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <fstream>

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

void findAllBishopMagicNumbers(vector<bitboard> masks)
{
    uint16_t magicNumbers[64] = {0};
    ofstream myfile;
    myfile.open("bishopMagics.txt");
    for (int i = 0; i < masks.size(); i++)
    {
        bitboard magicNumber = findMagicNumber(masks[i]);
        magicNumbers[i] = magicNumber;

        myfile << hex << magicNumber << endl;
    }
    myfile.close();
}

int main()
{
    vector<bitboard> masks = generateBishopMasks();
    findAllBishopMagicNumbers(masks);
    // unordered_set<bitboard> variations;
    // generateBlockerVariations(masks[0], 0, variations);
    // printUnorderedSet(variations);
    // for (auto i = masks.begin(); i != masks.end(); i++)
    // {
    //     displayBoard(*i);
    // }
    return 0;
}
