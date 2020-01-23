
typedef unsigned long long bitboard;

namespace masks
{
// Half board masks
const bitboard halfRowBottom = 4294967295ULL;
const bitboard halfColRight = 1085102592571150095ULL;

// Quarter board masks
const bitboard row78 = 281470681743360ULL;
const bitboard row34 = 65535;
const bitboard column56 = 3472328296227680304ULL;
const bitboard column12 = 217020518514230019ULL;

// Row masks
const bitboard row8 = 18374686479671623680ULL;
const bitboard row7 = 71776119061217280ULL;
const bitboard row6 = 280375465082880ULL;
const bitboard row5 = 1095216660480ULL;
const bitboard row4 = 4278190080ULL;
const bitboard row3 = 16711680ULL;
const bitboard row2 = 65280ULL;
const bitboard row1 = 255ULL;

// Column masks
const bitboard column8 = 9259542123273814144ULL;
const bitboard column7 = 4629771061636907072ULL;
const bitboard column6 = 2314885530818453536ULL;
const bitboard column5 = 1157442765409226768ULL;
const bitboard column4 = 578721382704613384ULL;
const bitboard column3 = 289360691352306692ULL;
const bitboard column2 = 144680345676153346ULL;
const bitboard column1 = 72340172838076673ULL;

const bitboard bitboardMax = 0xffffffffffffffffULL;

const bitboard rows[] = {row1, row2, row3, row4, row5, row6, row7, row8};
const bitboard columns[] = {column1, column2, column3, column4, column5, column6, column7, column8};

const bitboard ldiag1 = 72057594037927936ULL;
const bitboard ldiag2 = 144396663052566528ULL;
const bitboard ldiag3 = 288794425616760832ULL;
const bitboard ldiag4 = 577588855528488960ULL;
const bitboard ldiag5 = 1155177711073755136ULL;
const bitboard ldiag6 = 2310355422147575808ULL;
const bitboard ldiag7 = 4620710844295151872ULL;
const bitboard ldiag8 = 9241421688590303745ULL;
const bitboard ldiag9 = 36099303471055874ULL;
const bitboard ldiag10 = 141012904183812ULL;
const bitboard ldiag11 = 550831656968ULL;
const bitboard ldiag12 = 2151686160ULL;
const bitboard ldiag13 = 8405024ULL;
const bitboard ldiag14 = 32832ULL;
const bitboard ldiag15 = 128ULL;

const bitboard ldiags[] = {ldiag1, ldiag2, ldiag3, ldiag4, ldiag5, ldiag6, ldiag7, ldiag8, ldiag9, ldiag10, ldiag11, ldiag12, ldiag13, ldiag14, ldiag15};

const bitboard rdiag1 = 9223372036854775808ULL;
const bitboard rdiag2 = 4647714815446351872ULL;
const bitboard rdiag3 = 2323998145211531264ULL;
const bitboard rdiag4 = 1161999622361579520ULL;
const bitboard rdiag5 = 580999813328273408ULL;
const bitboard rdiag6 = 290499906672525312ULL;
const bitboard rdiag7 = 145249953336295424ULL;
const bitboard rdiag8 = 72624976668147840ULL;
const bitboard rdiag9 = 283691315109952ULL;
const bitboard rdiag10 = 1108169199648ULL;
const bitboard rdiag11 = 4328785936ULL;
const bitboard rdiag12 = 16909320ULL;
const bitboard rdiag13 = 66052ULL;
const bitboard rdiag14 = 258ULL;
const bitboard rdiag15 = 1ULL;

const bitboard rdiags[] = {rdiag1, rdiag2, rdiag3, rdiag4, rdiag5, rdiag6, rdiag7, rdiag8, rdiag9, rdiag10, rdiag11, rdiag12, rdiag13, rdiag14, rdiag15};
}; // namespace masks
