#include "bitboard.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    // Magics m = Magics();
    BitBoard b = (BitBoard)0xF0FULL;
    // BBbinaryPrint(b ^ ((BitBoard)1 << 3));
    // BBbinaryPrint(popLeadingOne(b));

    permuteBishopOccupancy(b);
}
