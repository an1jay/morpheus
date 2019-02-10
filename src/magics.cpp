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

    srand(time(NULL));
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq) //TODO
    {

        valid = false;
        // make occupancy BB
        blankMoves = BlankBishopMoves[sq];
        blankMoves &= ~BB_Edges;
        // fill occs with all possible distinct relevant occupancies
        permuteBishopOccupancy(blankMoves, occs);
        std::cout << "Finding Magic for Square " << sq << std::endl;
        do
        {
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
                    BishopMagicAttacks[sq][index] = av;
                }
                else
                {
                    // std::cout << "else sq: " << sq << std::endl;
                    valid = false;
                    break;
                }
                valid = true;
            }
            if (valid)
            {
                BishopMagics[sq] = candidateMagic;
                std::cout << "Square " << sq << "  Magic " << candidateMagic << std::endl;
            }
        } while (!valid);
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
    // return (BitBoard)(rand() & 0xFFFFULL) << 48;
    return (((BitBoard)rand() & 0xFFFFULL) |
            (((BitBoard)rand() & 0xFFFFULL) << 16) |
            (((BitBoard)rand() & 0xFFFFULL) << 32) |
            (((BitBoard)rand() & 0xFFFFULL) << 48)) &
           (((BitBoard)rand() & 0xFFFFULL) |
            (((BitBoard)rand() & 0xFFFFULL) << 16) |
            (((BitBoard)rand() & 0xFFFFULL) << 32) |
            (((BitBoard)rand() & 0xFFFFULL) << 48)) &
           (((BitBoard)rand() & 0xFFFFULL) |
            (((BitBoard)rand() & 0xFFFFULL) << 16) |
            (((BitBoard)rand() & 0xFFFFULL) << 32) |
            (((BitBoard)rand() & 0xFFFFULL) << 48));
}

BitBoard random_BitBoard()
{
    BitBoard u1, u2, u3, u4;
    u1 = (BitBoard)(rand()) & 0xFFFF;
    u2 = (BitBoard)(rand()) & 0xFFFF;
    u3 = (BitBoard)(rand()) & 0xFFFF;
    u4 = (BitBoard)(rand()) & 0xFFFF;
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

BitBoard random_BitBoard_fewbits()
{
    return random_BitBoard() & random_BitBoard() & random_BitBoard();
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