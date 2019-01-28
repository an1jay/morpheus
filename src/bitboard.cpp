#include "bitboard.h"
#include "constants.h"
#include <bitset>
#include <iostream>

void prettyPrint(BitBoard b)
{
    std::cout << "|  8th R |  7th R |  6th R |  5th R |  4th R |  3rd R |  2nd R |  1st R |" << std::endl;
    std::cout << "|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|ABCDEFGH|" << std::endl;

    for (int r = NUM_RANKS-1; r >= 0; --r)
        {
            std::cout << "|" ;
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

void binaryPrint(BitBoard b)
{
    std::cout << std::bitset<64>(b) << std::endl;
}


void boardPrint(BitBoard b)
{
    std::cout << "  A B C D E F G H" << std::endl;
    for (int r = NUM_RANKS-1; r >= 0; --r)
    {
        std::cout << 1 + r << " ";
        for (int sq = 0; sq < NUM_SQUARES_LINE; ++sq)
        {
            // std::cout << r * NUM_SQUARES_LINE + sq << " " ; 
            if ((b >> (r * NUM_SQUARES_LINE + sq)) & (BitBoard)1)
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