// Need two bitboards per type of piece

#include <iostream>
#include <bitset>

#include "bitboard.hpp"
#include "helper.hpp"
#include "pieces/bishopMagics.hpp"
#include "pieces/rookMagics.hpp"
#include "pieces/knightMasks.hpp"
#include "pieces/kingMasks.hpp"
#include "pieces/pieceTypes.hpp"
using namespace std;
using namespace masks;
using namespace board;

// bitboard::bitboard(unsigned long long init)
// {

// }

// bitboard::~bitboard()
// {
// }

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

void ChessBoard::displayAll()
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
    displayBoard(boards.at(1).at(pieceIndices.at(PieceType::PAWN)));
    printf("All White\n");
    displayBoard(WHITE);
    printf("Overall Board\n");
    displayBoard(BOARD);
}

ChessBoard::ChessBoard()
{
    BLACK_PAWN = 71776119061217280ULL;
    BLACK_ROOK = 9295429630892703744ULL;
    BLACK_KNIGHT = 4755801206503243776ULL;
    BLACK_BISHOP = 2594073385365405696ULL;
    BLACK_QUEEN = 1152921504606846976ULL;
    BLACK_KING = 576460752303423488ULL;
    BLACK = BLACK_PAWN | BLACK_ROOK | BLACK_KNIGHT | BLACK_BISHOP | BLACK_QUEEN | BLACK_KING;

    WHITE_PAWN = 65280;
    WHITE_ROOK = 129;
    WHITE_KNIGHT = 66;
    WHITE_BISHOP = 36;
    WHITE_QUEEN = 16;
    WHITE_KING = 8;
    WHITE = WHITE_PAWN | WHITE_ROOK | WHITE_KNIGHT | WHITE_BISHOP | WHITE_QUEEN | WHITE_KING;

    WHITE_SQUARES = 12273903644374837845ULL;
    BLACK_SQUARES = ~WHITE_SQUARES;

    BOARD = BLACK | WHITE;

    boards.insert({(uint8_t)0, {BLACK_PAWN, BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK}});
    boards.insert({1, {WHITE_PAWN, WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE}});
    boards.insert({2, {BLACK_SQUARES, WHITE_SQUARES}});

    pieceIndices = unordered_map<PieceType, uint8_t>({{PieceType::PAWN, 0}, {PieceType::ROOK, 1}, {PieceType::KNIGHT, 2}, {PieceType::BISHOP, 3}, {PieceType::QUEEN, 4}, {PieceType::KING, 5}});
}

ChessBoard createBoard()
{
    return ChessBoard();
}

bool ChessBoard::isGameOver()
{
    return GameOver;
}

int ChessBoard::getTurnColour()
{
    return Turn;
}

bool ChessBoard::getPlayerColour()
{
    return PlayerColour;
}

void ChessBoard::setPlayerColour(bool colour)
{
    PlayerColour = colour;
    // cout << PlayerColour << endl;
}

void ChessBoard::displayCurrentBoard()
{
    displayBoard(BOARD);
}

bitboard applyMove(Move move, bitboard moveBoard)
{
    bitboard removal = ~(rows[move.startingPos.first] & columns[move.startingPos.second]);
    bitboard addition = rows[move.finalPos.first] & columns[move.finalPos.second];

    moveBoard &= removal;
    moveBoard |= addition;

    return moveBoard;
}

bool ChessBoard::checkPlayerMove(Move move)
{
    if (move.startingPos.first == -1)
    {
        cout << "Ouch" << endl;
        return false;
    }
    bitboard pieceTypeBoard = boards.at(getTurnColour()).at(pieceIndices.at(move.piece));

    // Generate board of player's colour, with the given starting position
    bitboard startBoard = pieceTypeBoard & (rows[move.startingPos.first] & columns[move.startingPos.second]);

    // cout << "startBoard" << endl;
    // displayBoard(pieceTypeBoard);
    // displayBoard(startBoard);
    if (startBoard == 0)
    {
        // Not the right position
        return false;
    }

    bitboard possibleMoves = generatePossibleMoves(move.piece, move.startingPos);

    // cout << "Possible moves: " << endl;
    // Generate board of player's colour, with the given starting position
    // cout << "Final row, column: " << endl;
    // cout << move.finalPos.first - 10 << endl;
    // displayBoard(rows[move.finalPos.first]);
    // displayBoard(columns[move.finalPos.second]);
    // displayBoard(possibleMoves);
    // displayBoard(BOARD);
    // displayBoard(WHITE_QUEEN);
    // displayBoard(WHITE);
    bitboard finalBoard = possibleMoves & (rows[move.finalPos.first] & columns[move.finalPos.second]);

    // cout << "final board"
    //      << ", first: " << move.finalPos.first << endl;
    // displayBoard(finalBoard);

    // Make the move on the temp board
    bitboard moveBoard = applyMove(move, BOARD);
    // cout << "Move board: " << endl;
    // displayBoard(moveBoard);

    bitboard kboard = 0;
    if (move.piece == PieceType::KING)
    {
        kboard = moveBoard & ~(BOARD);
    }
    else
    {
        kboard = getTurnColour() ? WHITE_KING : BLACK_KING;
    }

    bool check = isKingInCheck(getTurnColour(), moveBoard, kboard);
    // cout << "Is king in check? " << check << endl;
    // cout << "Final board: " << endl;
    // displayBoard(finalBoard);
    if (finalBoard == 0 || check)
    {
        // Not the right position
        return false;
    }

    return true;
}

bool ChessBoard::getEnPassant(bool colour, int file)
{
    if (file < 0 || file > 7)
    {
        return false;
    }
    return enPassant[(colour * 8) + file];
}

bitboard ChessBoard::naivePawnPossibleMoves(bool colour, uint8_t row, uint8_t col)
{
    // cout << "generating possible moves..." << endl;

    // Check upper or lower rows depending on the colour
    int offset = colour ? 1 : -1;
    bitboard r1 = rows[row + offset];

    // cout << "r1" << endl;
    // displayBoard(r1);

    bitboard r2 = rows[row + (offset * 2)];
    bitboard moves = 0;

    // int twoMovePos = colour ? 1 : 6;
    // if (row == twoMovePos) {
    //     // Check the next two positions for any pieces
    //     bitboard twoPosForward = rows[row - (2 * -1 * colour)] & columns[col] & BOARD;
    //     if (twoMovePos > 0) {

    //     }
    // }

    // Checking straight movement
    bitboard checker = columns[col] & BOARD;
    if ((checker & r1) == 0)
    {
        if ((checker & r2) == 0)
        {
            moves |= (r1 | r2) & columns[col];
        }
        else
        {
            moves |= r1 & columns[col];
        }
    }

    // Piece Capture
    bitboard oppColorBoard = colour ? BLACK : WHITE;
    bitboard left = col == 7 ? 0 : columns[col + 1];
    bitboard right = col == 0 ? 0 : columns[col - 1];
    bitboard captureBoard = oppColorBoard & r1 & (left | right);
    moves |= captureBoard;

    // En passant
    bitboard oppColourPawns = colour ? BLACK_PAWN : WHITE_PAWN;
    // If there are any pawns on the same row,
    bitboard enPassant = rows[row] & oppColourPawns;
    bitboard leftEnPassant = (enPassant & left);
    bitboard rightEnPassant = (enPassant & right);
    if (getEnPassant(!colour, col + 1) && leftEnPassant)
    {
        moves |= leftEnPassant;
    }
    if (getEnPassant(!colour, col - 1) && rightEnPassant)
    {
        moves |= rightEnPassant;
    }

    return moves;
}

bitboard ChessBoard::naiveBishopPossibleMoves(bool colour, uint8_t row, uint8_t col, bitboard startBoard)
{
    bitboard colourBoard = colour ? WHITE : BLACK;
    // generate the mask
    bitboard mask = generateBishopMask(row, col);
    // cout << "Mask for: " << row + 0 << ", " << col + 0 << endl;
    // displayBoard(mask);
    // cout << "Coloured board: " << endl;
    // displayBoard(colourBoard);
    // Get blockers -> the board itself
    // get the legal moves from it
    bitboard b = mask & startBoard;
    int index1 = row * 8 + col;
    int legalIndex = ((BishopMagics::bishopMagics[index1] * b) >> 51);
    bitboard oppLegal = BishopMagics::bishopLegals[index1][legalIndex];
    return (oppLegal & ~colourBoard);
}

bitboard ChessBoard::naiveKnightPossibleMoves(bool colour, uint8_t row, uint8_t col)
{
    // Check 8 positions.
    int index = row * 8 + col;
    bitboard colourBoard = colour ? WHITE : BLACK;
    // displayBoard(KnightMasks::knightMasks[index]);
    return KnightMasks::knightMasks[index] & ~(colourBoard & ~(1ULL << index));
}
bitboard ChessBoard::naiveRookPossibleMoves(bool colour, uint8_t row, uint8_t col, bitboard startBoard)
{
    bitboard colourBoard = colour ? WHITE : BLACK;
    // generate the mask
    bitboard mask = generateRookMask(row, col);
    // Get blockers -> the board itself
    // get the legal moves from it
    bitboard b = mask & startBoard;
    int index1 = row * 8 + col;
    int legalIndex = ((RookMagics::rookMagics[index1] * b) >> 50);
    bitboard oppLegal = RookMagics::rookLegals[index1][legalIndex];
    // displayBoard(oppLegal);
    // displayBoard(oppLegal & ~colourBoard);
    return (oppLegal & ~colourBoard);
}
bitboard ChessBoard::naiveQueenPossibleMoves(bool colour, uint8_t row, uint8_t col, bitboard startBoard)
{
    // cout << colour << endl;
    // cout << "Possible moves for the queen" << endl;
    // // displayBoard(naiveRookPossibleMoves(colour, row, col, startBoard));
    // cout << "OR " << endl;
    // displayBoard(naiveBishopPossibleMoves(colour, row, col, startBoard));
    return (naiveRookPossibleMoves(colour, row, col, startBoard) | naiveBishopPossibleMoves(colour, row, col, startBoard));
}
bitboard ChessBoard::naiveKingPossibleMoves(bool colour, uint8_t row, uint8_t col)
{
    int index = row * 8 + col;
    bitboard colourBoard = colour ? WHITE : BLACK;
    // displayBoard(KingMasks::kingMasks[index]);
    return KingMasks::kingMasks[index] & ~(colourBoard & ~(1ULL << index));
}

bitboard ChessBoard::getCurrentBoard()
{
    return BOARD;
}

bitboard ChessBoard::generatePossibleMoves(PieceType p, pair<int8_t, int8_t> indices, bitboard startBoard)
{
    if (startBoard = 0)
    {
        startBoard = BOARD;
    }
    bool colour = getTurnColour();
    switch (p)
    {
    case PieceType::PAWN:
    {
        bitboard pawnMoves = naivePawnPossibleMoves(colour, indices.first, indices.second);
        // cout << "Pawn moves:" << endl;
        // displayBoard(pawnMoves);
        return pawnMoves;
    }
    case PieceType::BISHOP:
    {
        bitboard bishopMoves = naiveBishopPossibleMoves(colour, indices.first, indices.second, startBoard);
        // displayBoard(bishopMoves);
        return bishopMoves;
    }
    case PieceType::KNIGHT:
    {
        return naiveKnightPossibleMoves(colour, indices.first, indices.second);
    }
    case PieceType::ROOK:
    {
        return naiveRookPossibleMoves(colour, indices.first, indices.second, startBoard);
    }
    case PieceType::QUEEN:
    {
        return naiveQueenPossibleMoves(colour, indices.first, indices.second, startBoard);
    }
    case PieceType::KING:
    {
        return naiveKingPossibleMoves(colour, indices.first, indices.second);
    }
    default:
        break;
    }
}

// Update the 3 boards that are affected by the move
void ChessBoard::makeMove(Move move)
{
    bool colour = getTurnColour();
    // if (getPlayerColour() != colour)
    // {
    //     cout << getPlayerColour() << endl;
    //     cout << colour << endl;
    //     cout << "Not the player's turn" << endl;
    //     return;
    // }
    bitboard removal = ~(rows[move.startingPos.first] & columns[move.startingPos.second]);
    bitboard addition = rows[move.finalPos.first] & columns[move.finalPos.second];

    bitboard pieceBoard = boards.at(colour).at(pieceIndices.at(move.piece));
    if (colour)
    {
        WHITE &= removal;
        WHITE |= addition;
    }
    else
    {
        BLACK &= removal;
        BLACK |= addition;
    }

    pieceBoard &= removal;
    pieceBoard |= addition;
    boards.at(colour).at(pieceIndices.at(move.piece)) = pieceBoard;
    // WHITE_PAWN = pieceBoard;

    BOARD &= removal;
    BOARD |= addition;

    endTurn();

    bitboard kboard = getTurnColour() ? WHITE_KING : BLACK_KING;
    if (isKingInCheck(getTurnColour(), BOARD, kboard))
    {
        // Check if any move can be played.

        cout << "Check!" << endl
             << endl;
    }

    // cout << "Changed" << endl;
    // displayBoard(BOARD);
    // displayBoard(WHITE);
    // displayBoard(boards.at(colour).at(pieceIndices.at(move.piece)));
}

bool ChessBoard::isKingInCheck(bool colour, bitboard moveBoard, bitboard kBoard)
{
    bool oppColour = !colour;
    vector<bitboard> oppBoards = boards.at(oppColour);
    bitboard oppColourBoard = colour ? BLACK : WHITE;
    bitset<64> kingBoard = kBoard;
    // cout << "King board: " << endl;
    // displayBoard(kingBoard.to_ullong());
    // Check rows and cols.
    int index = kingBoard._Find_first();
    int row = index / 8;
    int col = index % 8;
    int ldiag = findLDiag(row, col);
    int rdiag = findRDiag(row, col);
    int rowOffset = colour ? (row - 1) * 8 : (row + 1) * 8;
    // cout << "king row: " << row << endl;
    // cout << "king col: " << col << endl;

    // Check if king is checked by:
    // queen: both diag and row/col
    // bishop: diag
    // rook: row/col
    // pawn: two specific pos
    // knight: check if king is on opposite knight squares
    // bitboard qboard = oppBoards.at(pieceIndices.at(PieceType::QUEEN));
    // bitboard rboard = oppBoards.at(pieceIndices.at(PieceType::ROOK));
    // if ((qboard & rows[row]) || (qboard & columns[col]) || ) {
    //     return true;
    // }
    // else if ((rboard & rows[row]) || (rboard & columns[col])) {
    //     return true;
    // }

    bitboard bishopMoves = naiveBishopPossibleMoves(colour, row, col, moveBoard);
    bitboard rookMoves = naiveRookPossibleMoves(colour, row, col, moveBoard);
    bitboard queenMoves = bishopMoves | rookMoves;
    bitboard knightMoves = naiveKnightPossibleMoves(colour, row, col);
    bitboard kingMoves = naiveKingPossibleMoves(colour, row, col);
    bitboard pawnMoves = (1ULL << (rowOffset + col - 1)) | (1ULL << (rowOffset + col + 1));

    if ((rookMoves & oppBoards.at(pieceIndices.at(PieceType::ROOK))) || (bishopMoves & oppBoards.at(pieceIndices.at(PieceType::BISHOP))) ||
        (queenMoves & oppBoards.at(pieceIndices.at(PieceType::QUEEN))) ||
        (knightMoves & oppBoards.at(pieceIndices.at(PieceType::KNIGHT))) ||
        (kingMoves & oppBoards.at(pieceIndices.at(PieceType::KING))) ||
        (pawnMoves & oppBoards.at(pieceIndices.at(PieceType::PAWN))))
    {
        return true;
    }
    return false;
}

void ChessBoard::endTurn()
{
    Turn = !Turn;
}

int ChessBoard::getPieceIndex(PieceType piece)
{
    return pieceIndices.at(piece);
}

unordered_map<uint8_t, vector<bitboard>> ChessBoard::getBoards()
{
    return boards;
}

// bitboard ChessBoard::rowAndColBoardGenerator(bitboard board)
// {

//     return rows[findRow(board) - 1] & columns[findColumn(board) - 1];
// }

// int main()
// {
//     printf("Hello\n");

//     return 0;
// }
