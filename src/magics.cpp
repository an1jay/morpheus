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
    std::cout << "Constructing" << std::endl;
    initBishops();
    initRooks();
}

BitBoard Magics::AttackFor(Square sq, BitBoard occupancy, PieceType PT) const
{

    // BitBoard sqBB = BBgenerate(sq);
    switch (PT)
    {
    case PieceType::BISHOP:

        return BishopMagicAttacks[(int)sq][((occupancy & BlankBishopMoves[(int)sq] & ~BB_Edges) * BishopMagics[(int)sq]) >> (64 - BishopShifts[(int)sq])];
        break;
    case PieceType::ROOK:
        return RookMagicAttacks[(int)sq][((occupancy & BlankRookMoves[(int)sq] & ~BB_Edges) * RookMagics[(int)sq]) >> (64 - BishopShifts[(int)sq])];
        break;

    default:
        return BB_AllSquares;
        break;
    }
}

void Magics::initBishops()
{
    BitBoard blankMoves;
    BitBoard candidateMagic;
    BitBoard shifted;
    BitBoard av;
    int index;
    BitBoard occs[512];
    bool valid = false;

    srand(42);
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq) //TODO
    {

        valid = false;

        // do
        // {

        // make occupancy BB
        blankMoves = BlankBishopMoves[sq];
        blankMoves &= ~BB_Edges;

        // fill occs with all possible distinct relevant occupancies
        permuteBishopOccupancy(blankMoves, occs);
        std::cout << "Square " << sq << std::endl;

        do
        {
        start:
            // make bishop attacks zero
            for (int i = 0; i < BishopMax; ++i)
                BishopMagicAttacks[sq][i] = BB_AllSquares;

            // find a magic number
            do
            {
                candidateMagic = genRand();
                shifted = blankMoves * candidateMagic >> (64 - BishopShifts[sq]);
            } while (BBcount(shifted) < 6);

            // for each thing in occs hash it and add attacks to the bishopmagicattacks, checking for conflicts
            for (int o = 0; o < BishopMax; ++o)
            {
                av = ManualBishopAttacks((Square)sq, occs[o]);
                index = (occs[o] * candidateMagic) >> (64 - shift);
                if (BishopMagicAttacks[sq][index] == BB_AllSquares || BishopMagicAttacks[sq][index] == av)
                {

                    if (BishopMagicAttacks[sq][index] == BB_AllSquares)
                    {
                        BishopMagicAttacks[sq][index] = av;
                        if (sq == (int)Square::B2)
                        {
                            // std::cout << "magic : " << candidateMagic << "  appending av: " << std::endl;
                            // BBboardPrint(av);
                        }
                    }
                }
                else
                {
                    // std::cout << "else sq: " << sq << std::endl;
                    goto start;
                }
            }
            valid = true;
            BishopMagics[sq] = candidateMagic;
        } while (!valid);
        // std::cout << "Square " << sq << "  Magic " << candidateMagic << std::endl;
        // for (int x = 0; x < BishopMax; ++x)
        // {
        //     std::cout << BishopMagicAttacks[sq][x] << ",";
        // }
        // } while (!valid);

        // test validity of the magic we just found magic number
        // 1. A mask of legal moves (on a blank board) for the square
        // 2. Generate occupancies on that mask
        // 3. Calculate attacks from that square given the occupancy
        // 4. Hash the occupancies
        // 5.
        // Need to check that each occupancy after hashing points to the correct move vector for the position
        // EXTRA: Occupancies that result in the same move vector point to the same index of the movevector array

        // put in array if valid
    }
}
void Magics::initRooks()
{
    std::cout << "Not Implemented" << std::endl;
}

BitBoard genRand()
{
    // return (BitBoard)(rand() % (1 << 16)) << 48;
    return ((BitBoard)(rand() % (1 << 16)) |
            ((BitBoard)(rand() % (1 << 16)) << 16) |
            ((BitBoard)(rand() % (1 << 16)) << 32) |
            ((BitBoard)(rand() % (1 << 16)) << 48));
}

void permuteBishopOccupancy(BitBoard moveMask, BitBoard *occs)
{
    BitBoard interim;
    int numOnes = BBcount(moveMask);
    int onesLocation[numOnes];
    int onesCounter = 0;

    for (int i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        if (BBgenerate((Square)i) & moveMask)
        {
            onesLocation[onesCounter] = i;
            onesCounter++;
        }
    }

    for (BitBoard n = 0; n < BBgenerate((Square)numOnes); n++)
    {
        interim = 0ULL;
        for (int x = 0; x <= numOnes; x++)
        {
            if (BBgenerate((Square)x) & n)
            {
                interim |= BBgenerate((Square)onesLocation[x]);
            }
        }
        occs[n] = interim;
    }
}