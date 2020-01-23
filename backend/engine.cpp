
#include <iostream>
#include "boards/bitboard.hpp"
using namespace std;
using namespace masks;

bitboard BLACK_PAWN = 71776119061217280ULL;
bitboard BLACK_ROOK = 9295429630892703744ULL;
bitboard BLACK_KNIGHT = 4755801206503243776ULL;
bitboard BLACK_BISHOP = 2594073385365405696ULL;
bitboard BLACK_QUEEN = 1152921504606846976ULL;
bitboard BLACK_KING = 576460752303423488ULL;
bitboard BLACK = BLACK_PAWN | BLACK_ROOK | BLACK_KNIGHT | BLACK_BISHOP | BLACK_QUEEN | BLACK_KING;

bitboard WHITE_PAWN = 65280;
bitboard WHITE_ROOK = 129;
bitboard WHITE_KNIGHT = 66;
bitboard WHITE_BISHOP = 36;
bitboard WHITE_QUEEN = 16;
bitboard WHITE_KING = 8;
bitboard WHITE = WHITE_PAWN | WHITE_ROOK | WHITE_KNIGHT | WHITE_BISHOP | WHITE_QUEEN | WHITE_KING;

bitboard WHITE_SQUARES = 12273903644374837845ULL;
bitboard BLACK_SQUARES = ~WHITE_SQUARES;

bitboard BOARD = BLACK | WHITE;

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

void displayAll()
{
    printf("Black King\n");
    displayBoard(BLACK_KING);
    printf("Black Queen\n");
    displayBoard(BLACK_QUEEN);
    printf("Black Rook\n");
    displayBoard(BLACK_ROOK);
    printf("Black Squares\n");
    displayBoard(BLACK_SQUARES);
    printf("Black Bishop\n");
    displayBoard(BLACK_BISHOP);
    printf("Black Knight\n");
    displayBoard(BLACK_KNIGHT);
    printf("Black Pawn\n");
    displayBoard(BLACK_PAWN);
    printf("All Black\n");
    displayBoard(BLACK);
    printf("White King\n");
    displayBoard(WHITE_KING);
    printf("White Queen\n");
    displayBoard(WHITE_QUEEN);
    printf("White Rook\n");
    displayBoard(WHITE_ROOK);
    printf("White Squares\n");
    displayBoard(WHITE_SQUARES);
    printf("White Bishop\n");
    displayBoard(WHITE_BISHOP);
    printf("White Knight\n");
    displayBoard(WHITE_KNIGHT);
    printf("White Pawn\n");
    displayBoard(WHITE_PAWN);
    printf("All White\n");
    displayBoard(WHITE);
    printf("Overall Board\n");
    displayBoard(column1);
}

int main()
{
    displayAll();
    // ch.generateMoves();
    return 0;
}
