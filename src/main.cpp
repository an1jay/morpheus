#include "bitboard.h"
#include "constants.h"
#include "magics.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <bitset>
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
    // BitBoard b = 0x11235F0089F;
    // Square sq = Square::H8;
    // Magics m = Magics(true);

    // std::cout << "Occupancy" << std::endl;
    // BBboardPrint(b);

    // std::cout << "Manual Attacks" << std::endl;
    // BBboardPrint(ManualRookAttacks(sq, b));

    // std::cout << "Magic Attacks" << std::endl;
    // BBboardPrint(m.AttackFor(sq, b, PieceType::ROOK));

    // Move testnum = (1ULL << 6) - 1;
    // std::cout << std::bitset<32>(testnum) << std::endl;
    std::cout
        << "ORIGIN_SQ_MASK" << std::bitset<32>(ORIGIN_SQ_MASK) << std::endl;
    std::cout
        << "TARGET_SQ_MASK" << std::bitset<32>(TARGET_SQ_MASK) << std::endl;
    std::cout
        << "COLOR_MASK    " << std::bitset<32>(COLOR_MASK) << std::endl;
    std::cout
        << "PIECE_MASK    " << std::bitset<32>(PIECE_MASK) << std::endl;
    std::cout
        << "CAPTURE_MASK  " << std::bitset<32>(CAPTURE_MASK) << std::endl;
    std::cout
        << "PROMOTION_MASK" << std::bitset<32>(PROMOTION_MASK) << std::endl;
    std::cout
        << "CASTLE_MASK   " << std::bitset<32>(CASTLE_MASK) << std::endl;
    std::cout
        << "ENPASSANT_MASK" << std::bitset<32>(ENPASSANT_MASK) << std::endl;

    return 0;
}
