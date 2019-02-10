#include "bitboard.h"
#include "magics.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    BitBoard b = 0xFF0000388ULL;
    // BitBoard middle_b = b & BB_NoEdges;
    // BitBoard occs[512] = {0ULL};
    // permuteBishopOccupancy(middle_b, occs);

    // std::cout << "number of ones in main" << BBcount(middle_b) << std::endl;
    // BBbinaryPrint(middle_b);

    BBboardPrint(b);
    std::cout << "Manual Bishop Attacks" << std::endl;
    BBboardPrint(ManualBishopAttacks(Square::C1, b));

    Magics m = Magics();
    BBboardPrint(m.AttackFor(Square::C1, b, PieceType::BISHOP));
    // for (int i = 0; i < 70; i++)
    // {
    //     std::cout << i << "  ";
    //     BBbinaryPrint(occs[i]);
    // }

    return 0;
}
