#ifndef MAGICNUMBERS_HPP
#define MAGICNUMBERS_HPP
#include "boards/bitboard.hpp"

namespace magicNumbers
{
bitboard rookMagics[] = {0xbe412503fc7354b3ULL, 0xa209cc237be4598eULL, 0x1fbd9a20a6c5bbf2ULL, 0x7d0cb1a3464ec113ULL, 0x30480d566c66974bULL, 0xa82ae2dd1cc8ac96ULL, 0x671f3d56fcfccf4cULL, 0x8efe2d7f4514496ULL, 0x327633f7434115ecULL, 0x786ad91a7e8d8a6eULL, 0xde5f7dd124706e4eULL, 0xa79db7181294cc6bULL, 0xe1067f6d27b3ed77ULL, 0xe4fa34cd00e87ecULL, 0xcfa1016ca8a8cb3ULL, 0xab666f9c29a6887fULL, 0xf89fcbdd652c68feULL, 0x21da9909a1c1e943ULL, 0xa80713849daf1b5bULL, 0x11a63c6cc1ab55c1ULL, 0x67d44170cb51fda5ULL, 0x3c90a250edbd7f56ULL, 0x49cfbcc647db68f6ULL, 0xa331d0dc1d4d9d44ULL, 0x13bca9752cea449fULL, 0xa2c6572b1477202fULL, 0xbafd232891f9738ULL, 0x2eadcd6568ef81f3ULL, 0x6339684c11e0bf92ULL, 0xbb2549b284af6105ULL, 0x712e199420da92b7ULL, 0xb160d03327e83f70ULL, 0x5569789cc4e68ebcULL, 0xd2714ed38053e42eULL, 0xeb95019b9f555979ULL, 0x3799ae06a965f9a7ULL, 0x1e68396bd819e237ULL, 0x4d3745f7e7d4b001ULL, 0x2d68c4914c0451e9ULL, 0x991d436b0eda8747ULL, 0xe4f290ef9335302cULL, 0xc6f8691d53b7e1d4ULL, 0x3a7f977763d40631ULL, 0x7f0b85fe183916dcULL, 0xa2320e79af38686aULL, 0x272e1df2931d6cfbULL, 0xec06f4a6b370680dULL, 0x699b62a74e4aa61ULL, 0x992a6eceaa1f8742ULL, 0x9fbfd662cb6b3cc1ULL, 0xece317145f9a2a00ULL, 0x20554ef819b186e5ULL, 0x7235388520a04b03ULL, 0x816c79331b7c6e4aULL, 0x7f134a4bd3202c14ULL, 0x72f201f431d95228ULL, 0x256f184ca6161b22ULL, 0x25aa00a352d1bf5aULL, 0x40f285d3bc60ee19ULL, 0x1fd2a3a49aad9f61ULL, 0xc0a675a1c12c96b2ULL, 0x447a822c49069a07ULL, 0xe63cceb57f65436bULL, 0x184663060d6c1aeeULL};

bitboard rookLegals[] = {

};

bitboard bishopMagics[] = {0xc22872eaf756feedULL, 0x943c69d093b70ddbULL, 0x8aae0267aa5a726bULL, 0x86a5f5fc53316efULL, 0xc721f427dd833f74ULL, 0x235de3ebc27d071ULL, 0x15b0a7b8eb7993b9ULL, 0x3d2cd466f93227eeULL, 0xec0ccc9b2dda99bdULL, 0x3182f0a4ff8d050cULL, 0x89d5ed96fb57b7efULL, 0xb37710cc000d97f3ULL, 0x1cadd74018a7ed67ULL, 0x267721c432aa9ca1ULL, 0x48dc204e58a59cdcULL, 0xf9507efbd2469e4bULL, 0xa92e20d447b26884ULL, 0xa8fd7291f126a82eULL, 0x6ae2a6311ceedd39ULL, 0xa8b4e852995df8daULL, 0x2d79f372933f4133ULL, 0xeea0745d4196e0c6ULL, 0xf8b0da28f9e9fcc1ULL, 0xe5aa7c1a680cdf6ULL, 0x1f05a11741495a02ULL, 0xc9a7dd7cb527cdf0ULL, 0x2359ec094cf91405ULL, 0x4e7ef990d0859744ULL, 0x73c0a6c009fcd02dULL, 0xf6467f2c7bf573b4ULL, 0x62f76d34e98cecefULL, 0x5a4dc473888a049eULL, 0xe2c8bf42c1e17d77ULL, 0x1880ca3d6e2bb74dULL, 0x6b6e1eef720541d5ULL, 0xfce5d6b5ed1103e1ULL, 0x8b7ac0460e356e2ULL, 0x74191f437bc5e82ULL, 0xa302ced5b6b838b1ULL, 0xdfd05f29ebab8bb4ULL, 0x9aaee1b9ecbc579dULL, 0x598f1dc5f20c0bd6ULL, 0x97accf59cd413424ULL, 0xdabf4d99aa9f88a2ULL, 0xf40a2793b7997938ULL, 0x85914f17aa6d3773ULL, 0xf90046bf34ea95cdULL, 0xc22974d63b9e0678ULL, 0xef9cb1c0254fc73cULL, 0x5e9dcda063edcb08ULL, 0x164de3ed678a0c7bULL, 0xb1989bc411490132ULL, 0x86c6d79c5dab704fULL, 0x802b927ba3539ecdULL, 0xca6aafa6aaaa3b31ULL, 0xf0dbd7ba983d85b5ULL, 0x9234c5eafacdf122ULL, 0x9085ed11d907a832ULL, 0x96e3361c0aaec839ULL, 0x9a8da308b19a6d2dULL, 0x563e4ec2ff8c94d2ULL, 0xe4d136e18ac26baaULL, 0xf9587b9124a511cdULL, 0x9f470733c4544c7bULL};
}; // namespace magicNumbers

#endif
