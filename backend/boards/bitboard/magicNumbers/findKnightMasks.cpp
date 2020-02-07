#include "../masks.hpp"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
using namespace std;

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

bool notInBounds(int row, int col)
{

    if (row < 0 || row > 7)
    {
        return true;
    }
    if (col < 0 || col > 7)
    {
        return true;
    }
    return false;
}

typedef struct _coordinate
{
    int x;
    int y;

    inline std::size_t operator()(const std::pair<int, int> &v) const
    {
        return v.first * 31 + v.second;
    }
} Coordinate;

void findKnightMasks()
{
    ofstream myfile;
    myfile.open("knightMasks.txt");
    myfile << "bitboard knightMasks[] = { ";
    // unordered_set<Coordinate> moves;
    vector<Coordinate> moves = {{1, 2}, {2, 1}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << i << ", " << j << endl;
            bitboard mask = 0;
            for (auto move : moves)
            {
                int row = i + move.x;
                int col = j + move.y;
                // cout << row << ", " << col << endl;
                // cout << move.first << ", " << move.second << endl;
                if (notInBounds(row, col))
                {
                    continue;
                }
                // cout << row << ", " << col << endl;

                mask |= 1ULL << ((row * 8) + col);
            }
            displayBoard(mask);
            myfile << "0x" << hex << mask << "ULL, ";
        }
    }

    myfile.close();
}

int main()
{
    findKnightMasks();
    return 0;
}
