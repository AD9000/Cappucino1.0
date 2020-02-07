#include <unordered_map>
using namespace std;

#define PIECE_TYPE uint8_t

class board
{
private:
    // List of pieces on the board
    unordered_map<PIECE_TYPE, pair<uint8_t, uint8_t>> pieces;
public:
    board(/* args */);
    ~board();
};

board::board(/* args */)
{
    
}
