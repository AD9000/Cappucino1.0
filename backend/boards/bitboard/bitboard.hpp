#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include "../masks.hpp"
// class bitboard
// {
// private:
//     unsigned long long board = 0;

// public:
//     bitboard(unsigned long long board);
//     ~bitboard();
// };

// #include "board.hpp"

class ChessBoard
{
private:
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

    // 1 or true means white's turn, 0 or false means black's turn
    // White starts first
    bool Turn = 1;

public:
    void displayAll();
    void displayBoard(bitboard);
    void generateMoves();
    int findRows(bitboard);
    int findColumns(bitboard);
    // bitboard rowAndColBoardGenerator(bitboard);
    bitboard generateRookMoves(bitboard, bitboard);
    // void generateMoves();
    // void generateMoves();
    // void generateMoves();
    // void generateMoves();
};

ChessBoard createBoard();

#endif
