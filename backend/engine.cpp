
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

bool checkInput(string move)
{
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
    return check;
}

void validateMove(string move)
{
    // Checking if move is valid
}

bool userMove(ChessBoard &board)
{
    while (true)
    {
        cout << endl;
        board.displayCurrentBoard();
        cout << endl;
        cout << "Your move..." << endl;
        string move;
        cin >> move;
        for (char &c : move)
        {
            c = tolower(c);
        }
        checkQuit(move);
        if (!checkInput(move))
        {
            continue;
        }

        // Valid Input. Check the move
        validateMove(move);

        break;
    }
    return true;
}

int main()
{
    // Create a chess board
    ChessBoard board = ChessBoard();

    // Ask player to choose a side
    if (!playerSetup(board))
    {
        exit(1);
    }

    cout << "Starting..." << endl;

    while (!board.isGameOver())
    {
        // Ask user to play a move
        userMove(board);

        break;
    }

    return 0;
}
