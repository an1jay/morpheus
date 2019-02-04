#include "bitboard.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    BitBoard b = 0xFF00FF0009FFULL;
    BBboardPrint(b);
    BBboardPrint(ManualBishopAttacks(Square::D4, b));
    BBboardPrint(ManualRookAttacks(Square::D4, b));
    // permuteBishopOccupancy(b);
    // BitBoard b = Diagonal(Square::E5);
    // BBboardPrint(b);
    // b = AntiDiagonal(Square::D4);
    // BBboardPrint(b);
}
