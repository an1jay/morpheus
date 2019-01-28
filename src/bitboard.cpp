#include "bitboard.h"
#include "constants.h"
#include <bitset>
#include <iostream>

void prettyPrint(BitBoard b)
{
    std::cout << "|  8th R |  7th R |  6th R |  5th R |  4th R |  3rd R |  2nd R |  1st R |" << std::endl;
    for (size_t r = 0; r < NUM_RANKS; ++r)
    {
        std::cout << "|";
        for (size_t sq = 0; sq < NUM_SQUARES_LINE; ++sq)
        {
            if ((b >> (NUM_SQUARES_BOARD - 1 - (r * NUM_SQUARES_LINE + sq))) & 1)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << "-";
            }
        }
    }
    std::cout << "|" << std::endl
              << "|  8th R |  7th R |  6th R |  5th R |  4th R |  3rd R |  2nd R |  1st R |" << std::endl;
}
void binaryPrint(BitBoard b)
{
    std::cout << std::bitset<64>(b) << std::endl;
}
void boardPrint(BitBoard b)
{
    std::cout << "  A B C D E F G H" << std::endl;
    for (size_t r = 0; r < NUM_RANKS; ++r)
    {
        std::cout << NUM_RANKS - r << " ";
        for (size_t sq = 0; sq < NUM_SQUARES_LINE; ++sq)
        {
            if ((b >> (NUM_SQUARES_BOARD - 1 - (r * NUM_SQUARES_LINE + sq))) & 1)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
}