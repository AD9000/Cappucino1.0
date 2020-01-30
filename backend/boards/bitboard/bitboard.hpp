#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <unordered_map>
#include <vector>
#include "../masks.hpp"
#include "pieces.hpp"
using namespace board;
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
    bitboard BLACK_PAWN;
    bitboard BLACK_ROOK;
    bitboard BLACK_KNIGHT;
    bitboard BLACK_BISHOP;
    bitboard BLACK_QUEEN;
    bitboard BLACK_KING;
    bitboard BLACK;

    bitboard WHITE_PAWN;
    bitboard WHITE_ROOK;
    bitboard WHITE_KNIGHT;
    bitboard WHITE_BISHOP;
    bitboard WHITE_QUEEN;
    bitboard WHITE_KING;
    bitboard WHITE;

    bitboard WHITE_SQUARES;
    bitboard BLACK_SQUARES;

    bitboard BOARD;
    unordered_map<uint8_t, vector<bitboard>> boards;
    unordered_map<PieceType, uint8_t> pieceIndices;
    // 1 or true means white's turn, 0 or false means black's turn
    // White starts first
    bool Turn = 1;
    bool GameOver = false;
    bool PlayerColour = 0;

public:
    ChessBoard();
    bool isGameOver();
    int getTurnColour();
    void setPlayerColour(int);
    void displayCurrentBoard();
    bool checkPlayerMove(Move);
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
