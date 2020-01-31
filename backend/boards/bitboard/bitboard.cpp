// Need two bitboards per type of piece

#include <iostream>
#include "bitboard.hpp"
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
    displayBoard(WHITE_PAWN);
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

void ChessBoard::displayBoard(bitboard board)
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
}

// Only generate legal moves as discarding non-legal bitboards is inefficient
void ChessBoard::generateMoves()
{
    bitboard oppColorPieces = Turn ? WHITE : BLACK;

    // Generate all possible masks
    generateRookMoves(Turn ? WHITE_ROOK : BLACK_ROOK, oppColorPieces);
}

bitboard ChessBoard::generateRookMoves(bitboard board, bitboard oppositeColorPieces)
{
    // Find the row and column
    int row = findRows(board);
    int column = findColumns(board);

    // Now examine each element on the row and column

    printf("%d\n%d\n", row, column);

    return 0;
}

// Uses binary search for speed!
int ChessBoard::findRows(bitboard board)
{

    // if ((board & halfRowBottom) > 0)
    // {
    //     if ((board & row78) > 0)
    //     {
    //         if (board & row8 > 0)
    //         {
    //             return 8;
    //         }
    //         else
    //         {
    //             return 7;
    //         }
    //     }
    //     else
    //     {
    //         if (board & row5 > 0)
    //         {
    //             return 5;
    //         }
    //         else
    //         {
    //             return 6;
    //         }
    //     }
    // }

    // if ((board & !halfRowBottom) > 0)
    // {
    //     if (board & row34 > 0)
    //     {
    //         if (board & row3 > 0)
    //         {
    //             return 3;
    //         }
    //         else
    //         {
    //             return 4;
    //         }
    //     }
    //     else
    //     {
    //         if (board & row1 > 0)
    //         {
    //             return 1;
    //         }
    //         else
    //         {
    //             return 2;
    //         }
    //     }
    // }
}

// Uses binary search for speed!
int ChessBoard::findColumns(bitboard board)
{

    if (board & halfColRight > 0)
    {
        if (board & column12 > 0)
        {
            if (board & column8 > 0)
            {
                return 8;
            }
            else
            {
                return 7;
            }
        }
        else
        {
            if (board & column5 > 0)
            {
                return 5;
            }
            else
            {
                return 6;
            }
        }
    }
    else
    {
        if (board & column56 > 0)
        {
            if (board & column3 > 0)
            {
                return 3;
            }
            else
            {
                return 4;
            }
        }
        else
        {
            if (board & column1 > 0)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }
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

void ChessBoard::setPlayerColour(bool colour)
{
    PlayerColour = colour;
}

void ChessBoard::displayCurrentBoard()
{
    displayBoard(BOARD);
}

bool ChessBoard::checkPlayerMove(Move move)
{
    if (move.startingPos.first == -1)
    {
        return false;
    }
    bitboard pieceTypeBoard = boards.at(getTurnColour()).at(pieceIndices.at(move.piece));

    // Generate board of player's colour, with the given starting position
    bitboard startBoard = pieceTypeBoard & (rows[move.startingPos.first] & columns[7 - move.startingPos.second]);

    if (startBoard == 0)
    {
        // Not the right position
        return false;
    }

    bitboard possibleMoves = generatePossibleMoves(move.piece, move.startingPos);

    // Generate board of player's colour, with the given starting position
    bitboard finalBoard = pieceTypeBoard & (rows[move.finalPos.first] & columns[7 - move.finalPos.second]);

    cout << "final board"
         << ", first: " << move.finalPos.first << endl;
    displayBoard(finalBoard);

    if (finalBoard == 0)
    {
        // Not the right position
        return false;
    }

    return true;
}

bool ChessBoard::getEnPassant()
{
    return enPassant;
}

bitboard ChessBoard::naivePawnPossibleMoves(uint8_t row, uint8_t col)
{
    // Check upper or lower rows depending on the colour
    int colour = getTurnColour();
    int colouredRow = colour ? row : 7 - row;
    int offset = colour ? 1 : -1;
    bitboard r1 = rows[colouredRow + offset];
    bitboard r2 = rows[colouredRow + (offset * 2)];
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
    bitboard left = col == 7 ? bitboardMax : columns[col + 1];
    bitboard right = col == 0 ? bitboardMax : columns[col - 1];
    bitboard captureBoard = oppColorBoard & r1 & (left | right);
    moves |= captureBoard;

    // En passant
    if (getEnPassant())
    {
    }
}

bitboard ChessBoard::generatePossibleMoves(PieceType p, pair<int8_t, int8_t> indices)
{
    switch (p)
    {
    case PieceType::PAWN:
        return naivePawnPossibleMoves(indices.first, indices.second);

    default:
        break;
    }
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
