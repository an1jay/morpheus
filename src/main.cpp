#include "bitboard.h"
#include "generateattacks.h"
#include "primitives.h"
#include <iostream>

int main()
{

    std::cout << "Pretty print" << std::endl;
    // prettyPrint(BB_Rank1);

    BitBoard occ = 56185285623985;
    BitBoard r = generateBitBoard(Square::D4);

    std::cout << "occupancy mask";
    BitBoard forward = occ & rookAttacksMask(r);
    boardPrint(forward);

    std::cout << "reverse occupancy mask";
    BitBoard reverse = reverseBoard(forward);
    boardPrint(reverse);

    forward -= 2 * r;
    reverse -= reverseBoard(2 * r);

    boardPrint((forward ^ reverseBoard(reverse)) & rookAttacksMask(r));

    std::cout << std::endl;
    binaryPrint(occ);
    std::cout << std::endl;

    std::cout << std::endl;
    binaryPrint((occ - 2 * r));
    std::cout << std::endl;

    // boardPrint(test);
    // std::cout << "knight attacks" << std::endl;
    // boardPrint(knightAttacks(test));

    // std::cout << "black pawn moves" << std::endl;
    // boardPrint(pawnMoves(test, Color::COLOR_BLACK));

    // std::cout << "white pawn Moves" << std::endl;
    // boardPrint(pawnMoves(test, Color::COLOR_WHITE));

    // std::cout << "bishop attacks" << std::endl;
    // boardPrint(bishopAttacks(test));
}
