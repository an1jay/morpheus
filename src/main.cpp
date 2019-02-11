#include "bitboard.h"
#include "magics.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    // bool valid;
    // for (int i = 0; i < 10; ++i)
    // {
    //     valid = true;
    //     b = genRand();
    //     std::cout << "*******************************************" << std::endl;
    //     std::cout << "Occupancy" << std::endl;
    //     BBboardPrint(b);

    //     for (int sa = 0; sa < NUM_SQUARES_BOARD; ++sa)
    //     {
    //         sq = (Square)sa;

    //         valid = valid && ManualBishopAttacks(sq, b) == m.AttackFor(sq, b, PieceType::BISHOP);
    //     }
    //     std::cout << "Validity? " << valid << std::endl;
    //     std::cout << "*******************************************" << std::endl;
    // }
    BitBoard b = 0x11235F0089F;
    Square sq = Square::H8;
    Magics m = Magics(false);

    std::cout << "Occupancy" << std::endl;
    BBboardPrint(b);

    std::cout << "Manual Attacks" << std::endl;
    BBboardPrint(ManualRookAttacks(sq, b));

    std::cout << "Magic Attacks" << std::endl;
    BBboardPrint(m.AttackFor(sq, b, PieceType::ROOK));

    return 0;
}
