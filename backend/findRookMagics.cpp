#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
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

vector<uint64_t> generateRookPossibleMovesMasks()
{
    // For every index on the bitboard
    vector<uint64_t> masks(64);
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

// Bitwise operations for ultimate speed
bool isCountGreaterThan1(bitboard board)
{
    board &= board - 1;
    return board > 0;
}

int findRow(bitboard board)
{
    int len = 8;
    for (int i = 0; i < len; i++)
    {
        if (isCountGreaterThan1(board & rows[i]))
        {
            return i;
        }
    }
}

int findColumn(bitboard board)
{
    int len = 8;
    for (int i = 0; i < len; i++)
    {
        if (isCountGreaterThan1(board & columns[i]))
        {
            return i;
        }
    }
}

// bitboard getTopColBoard(bitboard andRes, int row, int col) {
//     bitboard topBoard = andRes;
//     bool check = true;
//     for (int i = row - 1; i > 0; i--) {
//         int pos = i * 8 + col;
//         if (check) {
//             // Check if zero
//             if ((topBoard & ~(1 << pos)) == 0) {
//                 check = true;
//             }
//         }
//         else {
//             // Set to 0

//         }
//     }
// }

bitboard getTop(int col, int row, bitboard blockers, bitboard andres)
{
    // Get the row and column of blockers
    int topRow = row;
    for (int i = row - 1; i > 0; i++)
    {
        if ((rows[i] & blockers) > 0)
        {
            topRow = i;
            break;
        }
    }

    if (topRow == row)
    {
        // Make everything above row 1
        int sh = ((8 - row) * 8) - 1;
        bitboard shift = bitboardMax << sh;
        shift = shift << 1;
        andres |= columns[col] & shift;
    }
    else if (topRow < row)
    {
        // Clear columns above toprow
        andres &= bitboardMax >> (topRow * 8);

        // Set rows between toprow and row to 1
        int sh = ((8 - row) * 8) - 1;
        bitboard shift = bitboardMax << sh;
        shift = shift << 1;
        andres |= columns[col] & (shift & (bitboardMax >> (topRow * 8)));
    }

    // printf("top half\n");
    // displayBoard(andres);
    return andres;
}

bitboard getBottom(int row, int col, bitboard blockers, bitboard andres)
{
    // Get the row and column of blockers
    int bottomRow = row;
    for (int i = row + 1; i < 7; i++)
    {
        if ((rows[i] & blockers) > 0)
        {
            bottomRow = i;
            break;
        }
    }

    if (bottomRow == row)
    {
        // Set everything below row to 1
        if (row != 7)
        {
            andres |= columns[col] & (bitboardMax >> ((row + 1) * 8));
        }
    }
    else if (bottomRow > row)
    {
        // Clear columns below bottomrow
        andres &= bitboardMax << ((7 - bottomRow) * 8);

        // Set rows between bottomrow and row to 1
        bitboard bottomShift = (bitboardMax << ((7 - bottomRow) * 8));
        // displayBoard(bottomShift);
        andres |= columns[col] & ((bitboardMax >> ((row + 1) * 8)) & bottomShift);
    }

    // printf("bottom half\n");
    // displayBoard(andres);
    return andres;
}

bitboard getLegalRowBitboard(int row, int col, bitboard mask, bitboard blockers)
{
    bitboard andRes = mask & blockers;
    // bitboard topCol = getTopColBoard(andRes, row, col);
    bitboard rowBitBoard = andRes;

    return getTop(col, row, blockers, getBottom(row, col, blockers, andRes));
}

bitboard getRight(int col, int row, bitboard blockers, bitboard andres)
{
    // Get the row and column of blockers
    int rightColumn = col;
    for (int i = col + 1; i < 7; i++)
    {
        if ((columns[i] & blockers) > 0)
        {
            rightColumn = i;
            break;
        }
    }

    printf("Right Column: %d, row: %d\n", rightColumn, row);

    if (rightColumn == col)
    {
        int rowShift = ((7 + row) % 8) * 8;
        // Make every column 1 to the right of col
        bitboard adder = 0;
        for (int i = col + 1; i < 8; i++)
        {
            adder |= columns[i];
        }

        andres |= adder & rows[row];
    }
    else if (rightColumn > col)
    {
        // Clear column to the right of rightcolumn
        bitboard clearer = 0;
        for (int i = rightColumn + 1; i < 8; i++)
        {
            clearer |= columns[i];
        }
        andres &= ~clearer;

        bitboard adder = 0;
        // Make everything between rightcolumn and col 1
        for (int i = col + 1; i < rightColumn; i++)
        {
            adder |= columns[i];
        }

        andres |= adder & rows[row];
    }

    // printf("right half\n");
    // displayBoard(andres);
    return andres;
}

bitboard getLeft(int col, int row, bitboard blockers, bitboard andres)
{
    // Get the row and column of blockers
    int leftColumn = col;
    for (int i = col - 1; i > 0; i++)
    {
        if ((columns[i] & blockers) > 0)
        {
            leftColumn = i;
            break;
        }
    }

    // printf("Left Column: %d\n", leftColumn);

    if (leftColumn == col && col != 0)
    {
        // Set everything to the left of col to 1
        int rowShift = row * 8;
        // Make every column 1 to the right of col
        for (int i = 0; i < col; i++)
        {
            andres |= (1 << (rowShift + i));
        }
    }
    else if (leftColumn < col)
    {
        // Clear column left of leftcolumn
        bitboard clearer = 0;
        for (int i = 0; i < leftColumn; i++)
        {
            clearer |= columns[i];
        }
        andres &= ~clearer;

        // Add 1 ones between leftcolumn and col
        int rowShift = row * 8;
        // Make every column 1 to the right of col
        for (int i = leftColumn + 1; i < col; i++)
        {
            andres |= (1 << (rowShift + i));
        }
    }

    // printf("half\n");
    // displayBoard(andres);
    return andres;
}

bitboard getLegalColumnBitboard(int row, int col, bitboard mask, bitboard blockers)
{
    bitboard andRes = mask & blockers;

    // bitboard leftCol = getTopColBoard(andRes, row, col);
    bitboard columnBitBoard = andRes;

    // printf("Together\n");
    // bitboard x = getLeft(col, row, blockers, andRes) & getRight(col, row, blockers, andRes);
    // displayBoard(x);
    bitboard left = getLeft(col, row, blockers, andRes);
    // displayBoard(left);
    // displayBoard(right);

    return getRight(col, row, blockers, left);
}

bitboard generateLegalMoveBitboard(bitboard mask, bitboard blockers)
{
    int row = findRow(mask);
    int column = findColumn(mask);
    // bitboard legalRow = getLegalRowBitboard(row, column, mask, blockers);
    return ((getLegalRowBitboard(row, column, mask, blockers) & columns[column]) | (rows[row] & getLegalColumnBitboard(row, column, mask, blockers)));
}

void generateAllPossibleRookMoves(uint64_t mask)
{
}

void generateRookMagics(unordered_map<uint16_t, bitboard> &rookMagics)
{
    vector<uint64_t> masks = generateRookPossibleMovesMasks();

    for (uint64_t mask : masks)
    {
        // Generating all possible blocker variations for the
        unordered_set<bitboard> variations;
        generateBlockerVariations(50, 0, variations);
        // vector<bitboard> possibleMoves = generateAllPossibleRookMoves(possibleMoves, mask);
    }

    for (int8_t i = 0; i < 64; i++)
    {
        displayBoard(masks[i]);
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
            if (generated.size() % 10000000000 == 0)
            {
                printf("%lu, %lu\n", hasher, generated.size());
            }
        }
        unordered_set<uint16_t> indices;
        for (bitboard variation : variations)
        {
            uint16_t index = (hasher * variation) >> 48;
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

void findAllRookMagicNumbers(vector<uint64_t> masks)
{
    uint16_t magicNumbers[64] = {0};
    ofstream myfile;
    myfile.open("rookMagics.txt");
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
    printf("The numbers are:\n");
    // unordered_map<uint16_t, bitboard> rookMagics;
    // generateRookMagics(rookMagics);
    cout << "starting" << endl;

    // printUnorderedSet(variations);

    vector<uint64_t> rmasks = generateRookPossibleMovesMasks();
    // displayBoard

    findAllRookMagicNumbers(rmasks);
    // findAllBishopMagicNumbers(bmasks);
    // testMagicNumber(masks[0], 6589861800102187713);

    // unordered_set<bitboard> v;
    // test1(masks[0], 0, v);
    // printUnorderedSet(v);

    // printUnorderedSet(variations);
    // int i = 0;
    // for (bitboard variation : variations)
    // {
    //     // displayBoard(masks[0]);
    //     // displayBoard(variation);
    //     // displayBoard(getLegalRowBitboard(findRow(masks[0]), findColumn(masks[0]), masks[0], variation));
    //     // displayBoard(getLegalColumnBitboard(findRow(masks[0]), findColumn(masks[0]), masks[0], variation));
    //     // bitboard legalBoard = generateLegalMoveBitboard(masks[0], variation);
    //     // break;
    // }

    // for (auto i = masks.begin(); i != masks.end(); i++)
    // {
    //     displayBoard(*i);
    // }
    // displayBoard(generateLegalMoveBitboard())
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
