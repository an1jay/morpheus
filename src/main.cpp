#include "bitboard.h"
#include "constants.h"
#include "magics.h"
#include "move.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <iostream>

int main()
{

    Magics m = Magics(true);
    std::cout << "Magics made" << std::endl;
    Position p = Position();
    p.Display();
    std::vector<Move> *move_vector = p.GenerateLegalMoves(m);
    for (auto n : *move_vector)
        std::cout << EnglishFromMove(n) << std::endl;

    // BitBoard b = BBgenerate(Square::A2);
    // BBboardPrint(b);
    // BBboardPrint(b << 7);

    return 0;
}
