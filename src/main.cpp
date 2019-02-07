#include "bitboard.h"
#include "magics.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    BitBoard b = 0xFF00FF000900ULL;

    BBboardPrint(b);
    std::cout << "Manual Bishop Attacks" << std::endl;
    BBboardPrint(ManualBishopAttacks(Square::B2, b));

    Magics m = Magics();
    BBboardPrint(m.AttackFor(Square::B2, b, PieceType::BISHOP));
}
