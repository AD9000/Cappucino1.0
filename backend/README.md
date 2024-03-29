# Cappucino - The brain

## How to play against the engine (In the terminal):

The commands are split with each letter. To make a move, you must put in the original position of the piece to be moved and the final piece to be moved. If the move is valid, the move is made, and the engine begins thinking. Otherwise, the user is prompted accordingly. The format is as follows:

1. Type of piece:

   - k - King
   - q - Queen
   - b - Bishop
   - n - Knight
   - r - Rook
   - p - Pawn

2. Original position of the piece to be moved. eg: b4

   - 1 letter for the file (columns marked a-h)
   - 1 number for the rank (rows numbered 1-8)

3. Final position of the piece to be moved, in the same format as the original position.

So, a valid move could be: **qb1b7**  
It would be interpreted as: Move the queen from b1 to b7.

**Note**: All commands are case insensitive.

## Possible Improvements:

1. Could halve the number of bitboards maintained by not splitting by colour. In that case, there would be no need to maintain a hashmap for accessing the boards either. All for the cost of 1 bitwise operation when checking each move. Since the tradeoff is accessing from some array, I think the engine would stand to benefit a lot from this change. Not to mention that there will be half the number of the boards to update on making every move. (MUST DO BEFORE BOARD EVALUATION)

2. Store the generated "possible moves" for the opponent at the end of evaluation. For speeding up the checking when the player plays the move. This can then be used when the engine plays the next move.
