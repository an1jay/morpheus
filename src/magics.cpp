#include "magics.h"
#include "bitboard.h"
#include "constants.h"
#include "movegen.h"
#include "primitives.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Magics::Magics()
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

    initBishops();
    initRooks();
}

Magics::~Magics()
{
    delete[] BishopMagicAttacks;
    delete[] RookMagicAttacks;
}

BitBoard Magics::AttackFor(Square sq, BitBoard occupancy, PieceType PT) const
{

    BitBoard index;
    BitBoard relevantOccupancy;
    switch (PT)
    {
    case PieceType::BISHOP:
        relevantOccupancy = occupancy & BlankBishopMoves[(int)sq] & BB_NoEdges;
        index = (relevantOccupancy * BishopMagics[(int)sq]) >> (64 - BishopShifts[(int)sq]);
        return BishopMagicAttacks[(int)sq][index]; // maybe or it with edges

    case PieceType::ROOK:
        relevantOccupancy = occupancy & BlankRookMoves[(int)sq] & BB_NoEdges;
        index = (relevantOccupancy * RookMagics[(int)sq]) >> (64 - RookShifts[(int)sq]);
        return RookMagicAttacks[(int)sq][index]; // maybe or it with edges

    default:
        return BB_AllSquares;
    }
}

void Magics::initBishops()
{
    // 1. For each square find a candidate magic
    // 2. For each possible occupancy, store attack vector in correct index, checking there is no collision
    // 3. If no collisions, we have valid magic
    srand(420);
    BitBoard candidateMagic;
    BitBoard blankMiddleMoves;
    BitBoard occupancy;
    BitBoard moves;
    BitBoard index;
    bool validMagic;
    int numTried;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        std::cout << "Finding Bishop Magic for Square " << sq << " ---- ";
        numTried = 0;

        // only care about middle 6x6 occupancies
        blankMiddleMoves = BlankBishopMoves[sq] & BB_NoEdges;
        // assume valid until proven otherwise
        validMagic = true;

        // inside this loop, occupancy is equal to every possible relevant occupancy
        do
        {
            // part of Carry Rippler (see https://www.chessprogramming.org/Traversing_Subsets_of_a_Set)
            occupancy = 0ULL;
            // std::cout << "Inside first loop" << std::endl;

            validMagic = true;                                  // assume valid till proven otherwise
            candidateMagic = genRand() & genRand() & genRand(); // find a random magic (see https://www.chessprogramming.org/Looking_for_Magics)
            ++numTried;
            // BBbinaryPrint(candidateMagic);
            // set bishop magics to full board
            for (int b = 0; b < BishopMax; b++)
            {
                BishopMagicAttacks[sq][b] = BB_AllSquares;
            }

            do
            {
                // std::cout << "Inside second loop" << std::endl;

                // BBbinaryPrint(occupancy);
                moves = ManualBishopAttacks((Square)sq, occupancy);
                index = (occupancy * candidateMagic) >> (64 - BishopShifts[sq]);
                // if (occupancy == b)
                // {
                //     std::cout << "we get occ" << std::endl;
                // }
                if (BishopMagicAttacks[sq][index] == moves || BishopMagicAttacks[sq][index] == BB_AllSquares)
                {
                    BishopMagicAttacks[sq][index] = moves;
                    // std::cout << "Valid magic" << std::endl;
                    // std::cout << "occupancy: " << std::endl;
                    // BBboardPrint(occupancy);
                }
                else
                {
                    validMagic = false;
                    // std::cout << "Invalid magic" << std::endl;

                    break;
                }

                // Carry Rippler trick to traverse all possible occupancies (see https://www.chessprogramming.org/Traversing_Subsets_of_a_Set)
                occupancy = (occupancy - blankMiddleMoves) & blankMiddleMoves;
            } while (occupancy);
        } while (!validMagic);

        // add candidateMagic if it is not an invalid magic
        BishopMagics[sq] = candidateMagic;
        std::cout << numTried << " tries " << std::endl;
        numTried = 0;
    }
}

void Magics::initRooks()
{
    std::cout << "Not Implemented" << std::endl;
}

BitBoard genRand()
{
    return (((BitBoard)rand() & 0xFFFFULL) |
            (((BitBoard)rand() & 0xFFFFULL) << 16) |
            (((BitBoard)rand() & 0xFFFFULL) << 32) |
            (((BitBoard)rand() & 0xFFFFULL) << 48));
}

// void permuteBishopOccupancy(BitBoard moveMask, BitBoard *occs)
// {
//     BitBoard interim;
//     int numOnes = BBcount(moveMask);
//     int onesLocation[numOnes];
//     int onesCounter = 0;

//     for (int i = 0; i < NUM_SQUARES_BOARD; i++)
//     {
//         if (BBgenerate((Square)i) & moveMask)
//         {
//             onesLocation[onesCounter] = i;
//             onesCounter++;
//         }
//     }

//     for (BitBoard n = 0; n < BBgenerate((Square)numOnes); n++)
//     {
//         interim = 0ULL;
//         for (int x = 0; x <= numOnes; x++)
//         {
//             if (BBgenerate((Square)x) & n)
//             {
//                 interim |= BBgenerate((Square)onesLocation[x]);
//             }
//         }
//         occs[n] = interim;
//     }
// }