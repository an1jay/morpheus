#include "bitboard.h"
#include "constants.h"
#include <bitset>
#include <iostream>

void BBbinaryPrint(const BitBoard b)
{
    std::cout << std::bitset<64>(b) << std::endl;
}

void BBprettyPrint(const BitBoard b)
{
    std::cout << "|  8th R |  7th R |  6th R |  5th R |  4th R |  3rd R |  2nd R |  1st R |" << std::endl;
    std::cout << "|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|" << std::endl;

    for (int r = NUM_RANKS - 1; r >= 0; --r)
    {
        std::cout << "|";
        for (int sq = 0; sq < NUM_SQUARES_LINE; ++sq)
        {
            // std::cout << r * NUM_SQUARES_LINE + sq << " " ;
            if ((b >> (r * NUM_SQUARES_LINE + sq)) & (BitBoard)1)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << "-";
            }
        }
    }
    std::cout << "|" << std::endl;
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

BitBoard generateBB(const Square sq)
{
    return (BitBoard)1 << (int)sq;
}

bool occupiedBB(const BitBoard b, const Square sq)
{
    return __builtin_popcount(b & generateBB(sq));
}