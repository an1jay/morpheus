#include "magics.h"
#include "bitboard.h"
#include "constants.h"
#include "movegen.h"
#include "primitives.h"
#include <iostream>
#include <stdlib.h>

Magics::Magics(bool useExisting)
{
    BishopMagicAttacks = new BitBoard[NUM_SQUARES_BOARD][BishopMax];
    RookMagicAttacks = new BitBoard[NUM_SQUARES_BOARD][RookMax];
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        // set bishop magics to full board
        for (int b = 0; b < BishopMax; b++)
        {
            BishopMagicAttacks[sq][b] = BB_AllSquares;
        }
        // set rook magics to full board
        for (int r = 0; r < RookMax; r++)
        {
            RookMagicAttacks[sq][r] = BB_AllSquares;
        }
    }
    std::cout << "Finding magic numbers" << std::endl;

    initBishops(useExisting);
    initRooks(useExisting);
}

Magics::~Magics()
{
    delete[] BishopMagicAttacks;
    delete[] RookMagicAttacks;
}

void Magics::PrintMagics() const
{
    printf("constexpr BitBoard ExistingBishopMagics[64] = {\n");
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        printf("%#010llxULL,", BishopMagics[sq]);
        if ((sq + 1) % 8 == 0)
        {
            printf("\n");
        }
    }
    printf("\n};\n");

    printf("constexpr ExistingBitBoard RookMagics[64] = {\n");
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        printf("%#010llxULL,", RookMagics[sq]);
        if ((sq + 1) % 8 == 0)
        {
            printf("\n");
        }
    }
    printf("\n};\n");
}

BitBoard Magics::AttackFor(Square sq, BitBoard occupancy, PieceType PT) const
{

    BitBoard index;
    BitBoard relevantOccupancy;
    BitBoard sqBB;
    switch (PT)
    {
    case PieceType::BISHOP:
        relevantOccupancy = occupancy & BlankBishopMoves[(int)sq] & BB_NoEdges;
        index = (relevantOccupancy * BishopMagics[(int)sq]) >> (64 - BishopShifts[(int)sq]);
        return BishopMagicAttacks[(int)sq][index];
        break;

    case PieceType::ROOK:
        sqBB = BBgenerate((Square)sq);
        relevantOccupancy = BlankRookMoves[(int)sq] & occupancy;
        for (int fr = 0; fr < 4; ++fr)
        {
            if ((BB_EdgeArray[fr] & sqBB) == BB_NoSquares)
            {
                relevantOccupancy &= ~BB_EdgeArray[fr];
            }
        }
        index = (relevantOccupancy * RookMagics[(int)sq]) >> (64 - RookShifts[(int)sq]);
        return RookMagicAttacks[(int)sq][index];
        break;

    default:
        return BB_AllSquares;
        break;
    }
}

void Magics::initBishops(bool useExisting)
{
    // 1. For each square find a candidate magic
    // 2. For each possible occupancy, store attack vector in correct index, checking there is no collision
    // 3. If no collisions, we have valid magic
    srand(420);
    BitBoard candidateMagic;
    BitBoard relevantMoveMask;
    BitBoard occupancy;
    BitBoard moves;
    BitBoard index;
    bool validMagic;
    int triedCount;
    int totalTried = 0;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        std::cout << "Finding Bishop Magic for Square " << sq << " ---- ";
        triedCount = 0;

        // only care about middle 6x6 occupancies
        relevantMoveMask = BlankBishopMoves[sq] & BB_NoEdges;
        // assume valid until proven otherwise
        validMagic = true;

        // inside this loop, occupancy is equal to every possible relevant occupancy
        do
        {
            // part of Carry Rippler (see https://www.chessprogramming.org/Traversing_Subsets_of_a_Set)
            occupancy = 0ULL;
            // std::cout << "Inside first loop" << std::endl;

            validMagic = true; // assume valid till proven otherwise
            if (useExisting)
                candidateMagic = ExistingBishopMagics[sq];
            else
                candidateMagic = genRand() & genRand() & genRand(); // find a random magic (see https://www.chessprogramming.org/Looking_for_Magics)
            ++triedCount;
            // set bishop magics to full board
            for (int b = 0; b < BishopMax; b++)
            {
                BishopMagicAttacks[sq][b] = BB_AllSquares;
            }

            do
            {
                moves = ManualBishopAttacks((Square)sq, occupancy);
                index = (occupancy * candidateMagic) >> (64 - BishopShifts[sq]);
                if (BishopMagicAttacks[sq][index] == moves || BishopMagicAttacks[sq][index] == BB_AllSquares)
                {
                    BishopMagicAttacks[sq][index] = moves;
                }
                else
                {
                    validMagic = false;
                    break;
                }

                // Carry Rippler trick to traverse all possible occupancies (see https://www.chessprogramming.org/Traversing_Subsets_of_a_Set)
                occupancy = (occupancy - relevantMoveMask) & relevantMoveMask;
            } while (occupancy);
        } while (!validMagic);

        // add candidateMagic if it is not an invalid magic
        BishopMagics[sq] = candidateMagic;
        std::cout << triedCount << " tries " << std::endl;
        totalTried += triedCount;
        triedCount = 0;
    }
    std::cout << "Total bishop tries " << totalTried << std::endl;
}

void Magics::initRooks(bool useExisting)
{
    // 1. For each square find a candidate magic
    // 2. For each possible occupancy, store attack vector in correct index, checking there is no collision
    // 3. If no collisions, we have valid magic
    srand(2049);
    BitBoard candidateMagic;
    BitBoard relevantMoveMask;
    BitBoard occupancy;
    BitBoard moves;
    BitBoard index;
    bool validMagic;
    int triedCount;
    int totalTried = 0;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        std::cout << "Finding Rook Magic for Square " << sq << " ---- ";
        triedCount = 0;

        // added complication for rooks - need to check whether on corner or edge and then need to look up
        BitBoard sqBB = BBgenerate((Square)sq);
        relevantMoveMask = BlankRookMoves[sq];
        for (int fr = 0; fr < 4; ++fr)
        {
            if ((BB_EdgeArray[fr] & sqBB) == BB_NoSquares)
            {
                relevantMoveMask &= ~BB_EdgeArray[fr];
            }
        }

        // assume valid until proven otherwise
        validMagic = true;

        // inside this loop, occupancy is equal to every possible relevant occupancy
        do
        {
            // part of Carry Rippler (see https://www.chessprogramming.org/Traversing_Subsets_of_a_Set)
            occupancy = 0ULL;
            validMagic = true; // assume valid till proven otherwise
            if (useExisting)
                candidateMagic = ExistingRookMagics[sq];
            else
                candidateMagic = genRand() & genRand() & genRand(); // find a random magic (see https://www.chessprogramming.org/Looking_for_Magics)
            ++triedCount;
            // set rook magics to full board
            for (int b = 0; b < RookMax; b++)
            {
                RookMagicAttacks[sq][b] = BB_AllSquares;
            }

            do
            {
                moves = ManualRookAttacks((Square)sq, occupancy);
                index = (occupancy * candidateMagic) >> (64 - RookShifts[sq]);
                if (RookMagicAttacks[sq][index] == moves || RookMagicAttacks[sq][index] == BB_AllSquares)
                {
                    RookMagicAttacks[sq][index] = moves;
                }
                else
                {
                    validMagic = false;
                    break;
                }

                // Carry Rippler trick to traverse all possible occupancies (see https://www.chessprogramming.org/Traversing_Subsets_of_a_Set)
                occupancy = (occupancy - relevantMoveMask) & relevantMoveMask;
            } while (occupancy);
        } while (!validMagic);

        // add candidateMagic if it is not an invalid magic
        RookMagics[sq] = candidateMagic;
        std::cout << triedCount << " tries " << std::endl;
        totalTried += triedCount;
        triedCount = 0;
    }
    std::cout << "Total rook tries " << totalTried << std::endl;
}

BitBoard genRand()
{
    return (((BitBoard)rand() & 0xFFFFULL) |
            (((BitBoard)rand() & 0xFFFFULL) << 16) |
            (((BitBoard)rand() & 0xFFFFULL) << 32) |
            (((BitBoard)rand() & 0xFFFFULL) << 48));
}
