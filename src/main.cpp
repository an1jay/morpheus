#include "bitboard.h"
#include "constants.h"
#include "magics.h"
#include "move.h"
#include "movegen.h"
#include "position.h"
#include "primitives.h"
#include <bitset>
#include <iostream>

int main()
{
    Position p = Position();
    std::vector<Move> *move_vector = p.GenerateLegalMoves();
    for (auto n : move_vector)
        std::cout << EnglishFromMove(n) << std::endl;

    return 0;
}
