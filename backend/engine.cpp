
#include <iostream>
#include <string>
#include "boards/bitboard/bitboard.hpp"
#include "boards/bitboard/pieces.hpp"
using namespace std;
using namespace masks;
using namespace board;

bool playerSetup(ChessBoard board)
{
    cout << "Please choose a side w/b" << endl;
    string ans;
    cin >> ans;

    if (ans[0] == 'w' || ans[0] == 'W')
    {
        board.setPlayerColour(0);
    }
    else if (ans[0] == 'b' || ans[0] == 'B')
    {
        board.setPlayerColour(1);
    }
    else
    {
        cout << "Invalid input" << endl;
        return false;
    }
    return true;
}

void tryAgain()
{
    cout << "Please try again. You can always type 'quit' to exit" << endl;
}

void checkQuit(string input)
{
    if (input.compare("quit") == 0)
    {
        cout << "Exiting..." << endl;
        exit(0);
    }
}

pair<bool, Move> getMove(string move)
{
    unordered_set<char> PieceValues({'k', 'q', 'b', 'n', 'r', 'p'});
    bool check = true;
    if (move.size() != 5)
    {
        cout << "Invalid move" << endl;
    }
    else if (PieceValues.find(move[0]) == PieceValues.end())
    {
        cout << "Could not find piece type: " << move[0] << endl;
        check = false;
    }
    else if (move[1] < 'a' || move[1] > 'h' || move[2] < '1' || move[2] > '8')
    {
        cout << "Invalid starting position: " << move[1] << move[2] << endl;
        check = false;
    }
    else if (move[3] < 'a' || move[3] > 'h' || move[4] < '1' || move[4] > '8')
    {
        cout << "Invalid Final position: " << move[3] << move[4] << endl;
        check = false;
    }
    if (!check)
    {
        tryAgain();
    }

    if (check)
    {
        Move pieceMove((PieceType)move[0], move[1], move[2], move[3], move[4]);

        // cout << "Start pos: " << pieceMove.startingPos.first + 0 << pieceMove.startingPos.second + 0 << endl;
        return make_pair(true, pieceMove);
    }
    else
    {
        Move temp;
        return make_pair(false, temp);
    }
    // board.generatePossibleMoves(PieceType::PAWN, make_pair(1, 6));
}

bool validateMove(Move &move, ChessBoard &board)
{
    // Checking if move is valid
    // At this point, piece type is valid so skip!

    // Check starting position has piece. And the right one. And the right colour
    bool check = board.checkPlayerMove(move);
    if (!check)
    {
        cout << "Invalid move: Either piece is not at the expected position or the piece cannot move to the final position" << endl;
    }

    return check;
}

void userMove(ChessBoard &board)
{
    bool valid = false;
    Move playerMove;
    while (!valid)
    {
        cout << endl;
        board.displayCurrentBoard();
        cout << endl;
        cout << "Your move..." << endl;
        string input;
        cin >> input;
        for (char &c : input)
        {
            c = tolower(c);
        }
        checkQuit(input);
        pair<bool, Move> move = getMove(input);
        if (!move.first)
        {
            continue;
        }

        playerMove = move.second;

        // Valid Input. Check the move
        valid = validateMove(move.second, board);
    }

    // Move must be validated by now. Make the move!
    board.makeMove(playerMove);
}

int main()
{
    // Create a chess board
    ChessBoard board = ChessBoard();
    // board.makeMove(getMove("pe2e4").second);
    // board.makeMove(getMove("qd1g4").second);
    // board.makeMove(getMove("qg4g7").second);
    // // board.makeMove(getMove("re3e7").second);
    // board.naiveQueenPossibleMoves(6, 1);
    // Ask player to choose a side
    if (!playerSetup(board))
    {
        exit(1);
    }

    // cout << "Starting..." << endl;

    while (!board.isGameOver())
    {
        // Ask user to play a move
        userMove(board);
        // break;
    }

    // board.displayAll();

    return 0;
}
