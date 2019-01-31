#include "bitboard.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    BitBoard b = 0xFULL;
    permuteBishopOccupancy(b);
}
