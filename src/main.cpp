#include "bitboard.h"
#include "magics.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{
    BitBoard b = BlankBishopMoves[0];
    BitBoard middle_b = b & BB_NoEdges;
    BitBoard *permutations = permuteBishopOccupancy(middle_b);

    // BBboardPrint(b);
    // std::cout << "Manual Bishop Attacks" << std::endl;
    // BBboardPrint(ManualBishopAttacks(Square::B2, b));

    // Magics m = Magics();
    // BBboardPrint(m.AttackFor(Square::B2, b, PieceType::BISHOP));
    for (int i = 0; i < 70; i++)
    {
        std::cout << i << "  ";
        BBbinaryPrint(permutations[i]);
    }

    free(permutations);
    return 0;
}
