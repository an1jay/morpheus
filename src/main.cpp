#include "bitboard.h"
#include "generateattacks.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{

    Position p = Position();
    p.Display();

    BitBoard b = generateBB(Square::A1);
    BBboardPrint(b);
}