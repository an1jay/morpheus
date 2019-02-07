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

        return BishopMagicAttacks[(int)sq][((occupancy & BlankBishopMoves[(int)sq] & ~BB_Edges) * BishopMagics[(int)sq]) >> (64 - shift)];
        break;
    case PieceType::ROOK:
        return RookMagicAttacks[(int)sq][((occupancy & BlankRookMoves[(int)sq] & ~BB_Edges) * RookMagics[(int)sq]) >> (64 - shift)];
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
    for (int sq = 0; sq < 1; ++sq) //TODO
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
        for (int o = 0; o < BishopMax; ++o)
        {
            BBbinaryPrint(occs[o]);
            if (!((occs[o] & ~BBgenerate(Square::G7)) == 0ULL && (occs[o] & BBgenerate(Square::G7)) != 0ULL))
            {
                std::cout << "its there" << std::endl;
                // BBbinaryPrint(occs[o]);
            }
        }

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
                shifted = blankMoves * candidateMagic >> (64 - shift);
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
                            std::cout << "magic : " << candidateMagic << "  appending av: " << std::endl;
                            BBboardPrint(av);
                        }
                    }
                }
                else
                {
                    std::cout << "else sq: " << sq << std::endl;
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

void permuteBishopOccupancy(BitBoard mask, BitBoard *arr)
{
    // BitBoard locs[9];
    BitBoard rv[512] = {(BitBoard)0};
    rv[0] = mask;
    int count = 1;
    AppendBishOcc(mask, rv, &count);
    // std::cout << "something in between" << std::endl;
    // for (size_t i = 0; i < 50; i++)
    // {
    //     BBbinaryPrint(rv[i]);
    // }

    arr = rv;
}

void AppendBishOcc(BitBoard b, BitBoard *arr, int *count)
{
    if (BBcount(b) == 1)
    {
        arr[(*count)] = b;
        arr[(*count) + 1] = 0;
        return;
    }

    BitBoard newb;
    bool randombool = false;

    for (int i = 0; i < 64 - __builtin_clzll((uint64_t)b); i++)
    {
        randombool = false;
        if (b & BBgenerate((Square)i))
        {
            newb = b ^ BBgenerate((Square)i);
            for (int n = 0; n <= *count; n++)
            {
                if (arr[n] == newb)
                {
                    randombool = true;
                    break;
                }
            }
            if (randombool)
            {
                continue;
            }
            arr[(*count)] = newb;
            // BBbinaryPrint(arr[(*count)]);
            // std::cout << "(*count)" << (*count) << " ";
            (*count)++;
            AppendBishOcc(arr[(*count) - 1], arr, count);
        }
    }
}

// BitBoard popLeadingOne(BitBoard b)
// {
//     int lz = __builtin_clzll((uint64_t)b);
//     // std::cout << "lz " << lz << std::endl;
//     // std::cout << "64 - lz" << 63 - lz << std::endl;
//     return (b ^ ((uint64_t)1 << (63 - lz)));
// }

// int positionLeadingOne(BitBoard b)
// {
//     int lz = __builtin_clzll((uint64_t)b);

//     return (63 - lz);
// }
