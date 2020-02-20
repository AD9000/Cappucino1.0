#include <iostream>
#include <bitset>

#include "boards/bitboard/bitboard.hpp"
#include "boards/bitboard/pieces/pieceTypes.hpp"
#include "engine.hpp"
using namespace std;

vector<Move> getPieceMoves(ChessBoard &board, PieceType piece, int index, bitboard startBoard)
{
    vector<Move> pieceMoves;
    int row = index / 8;
    int col = index % 8;

    pair<int8_t, int8_t> startPos = make_pair(row, col);

    bitset<64> possibleMoves = board.generatePossibleMoves(piece, startPos, startBoard);
    int moveIndex = possibleMoves._Find_first();
    while (moveIndex != 64)
    {
        int fRow = moveIndex / 8;
        int fCol = moveIndex % 8;
        pieceMoves.push_back(Move(piece, startPos, make_pair(fRow, fCol)));
        moveIndex = possibleMoves._Find_next(moveIndex);
    }
    return pieceMoves;
}

vector<vector<Move>> getPieceTypeMoves(ChessBoard &board, PieceType piece, bitboard pieceTypeBoard, bitboard startBoard)
{
    vector<vector<Move>> moves;
    bitset<64> piecesBoard = pieceTypeBoard;
    int index = piecesBoard._Find_first();
    while (index != 64)
    {
        vector<Move> pieceMoves = getPieceMoves(board, piece, index, startBoard);
        moves.push_back(pieceMoves);
        index = piecesBoard._Find_next(index);
    }
    return moves;
}

Move bruteForceMove(ChessBoard &board, bool colour)
{
    vector<vector<vector<Move>>> allMoves;
    vector<bitboard> colourBoards = board.getBoards().at(colour);
    vector<Move> possibleMoves;

    bitboard startBoard = board.getCurrentBoard();
    bitboard finalBoard = startBoard;

    for (PieceType piece : pieceTypes)
    {
        int pieceIndex = board.getPieceIndex(piece);
        // For each piece, build a move. Play it with 10% probability
        bitboard pieceBoard = colourBoards.at(pieceIndex);
        vector<vector<Move>> piecetypeMoves = getPieceTypeMoves(board, piece, pieceBoard, startBoard);

        // Play move with 10% probability
        if (rand() % 10 == 2)
        {
            bool moveMade = false;
            for (vector<Move> pieceMoves : piecetypeMoves)
            {
                for (Move move : pieceMoves)
                {
                    if ((!moveMade) && rand() % 10 == 5)
                    {
                        board.makeMove(move);
                        moveMade = true;
                        return Move();
                    }
                }
            }
        }

        allMoves.push_back(piecetypeMoves);
    }

    return allMoves.at(0).at(0).at(0);
}

Move chooseMove(ChessBoard &board)
{
    return bruteForceMove(board, board.getTurnColour());
}

void engineMove(ChessBoard &board)
{
    board.makeMove(chooseMove(board));
}
