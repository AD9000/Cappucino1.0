
typedef unsigned long long bitboard;

namespace masks
{
// Half board masks
const bitboard halfRowBottom = 4294967295ULL;
const bitboard halfColRight = 1085102592571150095ULL;

// Quarter board masks
const bitboard row34 = 281470681743360ULL;
const bitboard row78 = 65535;
const bitboard column34 = 3472328296227680304ULL;
const bitboard column78 = 217020518514230019ULL;

// Row masks
const bitboard row1 = 18374686479671623680ULL;
const bitboard row2 = 71776119061217280ULL;
const bitboard row3 = 280375465082880ULL;
const bitboard row4 = 1095216660480ULL;
const bitboard row5 = 4278190080ULL;
const bitboard row6 = 16711680ULL;
const bitboard row7 = 65280ULL;
const bitboard row8 = 255ULL;

// Column masks
const bitboard column1 = 9259542123273814144ULL;
const bitboard column2 = 4629771061636907072ULL;
const bitboard column3 = 2314885530818453536ULL;
const bitboard column4 = 1157442765409226768ULL;
const bitboard column5 = 578721382704613384ULL;
const bitboard column6 = 289360691352306692ULL;
const bitboard column7 = 144680345676153346ULL;
const bitboard column8 = 72340172838076673ULL;

const bitboard bitboardMax = 0xffffffffffffffffULL;

const bitboard rows[] = {row1, row2, row3, row4, row5, row6, row7, row8};
const bitboard columns[] = {column1, column2, column3, column4, column5, column6, column7, column8};
}; // namespace masks
