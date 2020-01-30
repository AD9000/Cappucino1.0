# Cappucino - The brain

## How to play against the engine:

The commands are split with each letter. To make a move, you must put in the original position of the piece to be moved and the final piece to be moved. If the move is valid, the move is made, and the engine begins thinking. Otherwise, the user is prompted accordingly. The format is as follows:

1. Type of piece:

   - k - King
   - q - Queen
   - b - Bishop
   - n - Knight
   - r - Rook
   - p - Pawn

2. Original position of the piece to be moved.

   - 1 letter for the file (columns marked a-h)
   - 1 number for the rank (rows numbered 1-8)
     eg: b4

3. Final position of the piece to be moved, in the same format as the original position.

All commands are case insensitive.

So, a valid move could be: qb1b7
Which means, move the queen from b1 to b7
