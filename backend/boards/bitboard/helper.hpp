#include <cstdint>
#include "masks.hpp"
using namespace masks;

int findLDiag(int, int);
int findRDiag(int, int);
bitboard generateBishopMask(uint8_t, uint8_t);
bitboard generateRookMask(uint8_t, uint8_t);
void displayBoard(bitboard board);
