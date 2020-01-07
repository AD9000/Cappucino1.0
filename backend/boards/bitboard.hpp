#ifndef BITBOARD_HPP
#define BITBOARD_HPP
// class bitboard
// {
// private:
//     unsigned long long board = 0;

// public:
//     bitboard(unsigned long long board);
//     ~bitboard();
// };

// #include "board.hpp"

typedef unsigned long long bitboard;

namespace masks
{
// Half board masks
const bitboard halfRowBottom = 4294967295ULL;
const bitboard halfColRight = 1085102592571150095ULL;

// Quarter board masks
const bitboard row34 = 281470681743360ULL;
const bitboard row78 = 65535;
const bitboard column34 = 3472328296227680304ULL;
const bitboard column78 = 217020518514230019ULL;

// Row masks
const bitboard row1 = 18374686479671623680ULL;
const bitboard row2 = 71776119061217280ULL;
const bitboard row3 = 280375465082880ULL;
const bitboard row4 = 1095216660480ULL;
const bitboard row5 = 4278190080ULL;
const bitboard row6 = 16711680ULL;
const bitboard row7 = 65280ULL;
const bitboard row8 = 255ULL;

// Column masks
const bitboard column1 = 9259542123273814144ULL;
const bitboard column2 = 4629771061636907072ULL;
const bitboard column3 = 2314885530818453536ULL;
const bitboard column4 = 1157442765409226768ULL;
const bitboard column5 = 578721382704613384ULL;
const bitboard column6 = 289360691352306692ULL;
const bitboard column7 = 144680345676153346ULL;
const bitboard column8 = 72340172838076673ULL;

const bitboard rows[] = {row1, row2, row3, row4, row5, row6, row7, row8};
const bitboard columns[] = {column1, column2, column3, column4, column5, column6, column7, column8};
}; // namespace masks

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
    int findRow(bitboard);
    int findColumn(bitboard);
    bitboard rowAndColBoardGenerator(bitboard);
    bitboard generateRookMoves(bitboard, bitboard);
    // void generateMoves();
    // void generateMoves();
    // void generateMoves();
    // void generateMoves();
};

#endif
