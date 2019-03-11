#include "bitboard.h"
#include "constants.h"
#include <bitset>
#include <iostream>

void BBbinaryPrint(const BitBoard b)
{
    std::cout << std::bitset<64>(b) << std::endl;
}

void BBboardPrint(const BitBoard b)
{
    for (int r = NUM_RANKS - 1; r >= 0; --r)
    {
        std::cout << std::endl
                  << "  |---|---|---|---|---|---|---|---|" << std::endl;
        std::cout << 1 + r << " |";
        for (int sq = 0; sq < NUM_SQUARES_LINE; ++sq)
        {
            if ((b >> (r * NUM_SQUARES_LINE + sq)) & (BitBoard)1)
            {
                std::cout << " X |";
            }
            else
            {
                std::cout << " - |";
            };
        }
    }
    std::cout << std::endl
              << "  |---|---|---|---|---|---|---|---|" << std::endl
              << std::endl
              << "    A   B   C   D   E   F   G   H" << std::endl
              << std::endl;
}

BitBoard BBgenerate(const Square sq)
{
    return (BitBoard)1 << (int)sq;
}

bool BBoccupied(const BitBoard b, const Square sq)
{
    return __builtin_popcountll(b & BBgenerate(sq));
}

int BBcount(const BitBoard b)
{
    return __builtin_popcountll(b);
}

BitBoard BBreverse(const BitBoard b)
{
    BitBoard rev = b;
    rev = ((rev >> 1) & ((BitBoard)0x55555555 << 32 | 0x55555555)) | ((rev << 1) & ((BitBoard)0xaaaaaaaa << 32 | 0xaaaaaaaa));
    rev = ((rev >> 2) & ((BitBoard)0x33333333 << 32 | 0x33333333)) | ((rev << 2) & ((BitBoard)0xcccccccc << 32 | 0xcccccccc));
    rev = ((rev >> 4) & ((BitBoard)0x0f0f0f0f << 32 | 0x0f0f0f0f)) | ((rev << 4) & ((BitBoard)0xf0f0f0f0 << 32 | 0xf0f0f0f0));
    rev = ((rev >> 8) & ((BitBoard)0x00ff00ff << 32 | 0x00ff00ff)) | ((rev << 8) & ((BitBoard)0xff00ff00 << 32 | 0xff00ff00));
    rev = ((rev >> 16) & ((BitBoard)0x0000ffff << 32 | 0x0000ffff)) | ((rev << 16) & ((BitBoard)0xffff0000 << 32 | 0xffff0000));
    rev = (rev >> 32) | (rev << 32);
    return rev;
}