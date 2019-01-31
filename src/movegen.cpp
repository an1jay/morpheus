#include "movegen.h"
#include "bitboard.h"
#include "constants.h"
#include "primitives.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

Magics::Magics()
{
    initBishops();
    initRooks();
}

BitBoard Magics::AttackFor(Square sq, BitBoard occupancy, PieceType PT) const
{
    BitBoard sqBB = generateBB(sq);
    switch (PT)
    {
    case PieceType::BISHOP:
        return BishopMagicAttacks[(occupancy * BishopMagics[(int)sq]) >> (64 - shift)];
        break;
    case PieceType::ROOK:
        return RookMagicAttacks[(occupancy * RookMagics[(int)sq]) >> (64 - shift)];
        break;

    default:
        return BB_AllSquares;
        break;
    }
}

void Magics::initBishops()
{
    BitBoard blankMoves;
    BitBoard randnum;
    BitBoard shifted;
    srand(time(NULL));
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        blankMoves = BlankBishopMoves[sq];
        blankMoves &= ~BB_Edges;
        do
        {
            randnum = genRand();
            shifted = blankMoves * randnum >> (64 - shift);
        } while (countBB(shifted) < 6);
        BishopMagics[sq] = randnum;
        std::cout << "Square " << sq << "  Magic " << randnum << std::endl;
        // BBboardPrint(shifted);
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

void permuteBishopOccupancy(BitBoard b)
{
    // BitBoard locs[9];
    BitBoard rv[512] = {(BitBoard)0};
    NewAppendBishOcc(b, rv, 0);
    for (size_t i = 0; i < 512; i++)
    {
        BBbinaryPrint(rv[i]);
    }

    // return rv;
}

void appendBishOcc(BitBoard b, BitBoard *arr, int count)
{
    if (countBB(b) == 1)
    {
        arr[count] = b;
        arr[count + 1] = BB_NoSquares;
    }
    else
    {
        arr[count] = b;
        appendBishOcc(popLeadingOne(b), arr, count + 1);
    }
}

void NewAppendBishOcc(BitBoard b, BitBoard *arr, int count)
{
    // std::cout << "NEw Append";
    arr[count] = b;
    // for (int i = 0; i < 64 - __builtin_clzll((uint64_t)b); i++)
    for (int i = 0; i < 64; i++)
    {
        if ((b >> i) & 1)
        {
            NewAppendBishOcc(b ^ ((BitBoard)1 << i), arr, count + 1);
        }
    }
}

BitBoard popLeadingOne(BitBoard b)
{
    int lz = __builtin_clzll((uint64_t)b);
    // std::cout << "lz " << lz << std::endl;
    // std::cout << "64 - lz" << 63 - lz << std::endl;
    return (b ^ ((uint64_t)1 << (63 - lz)));
}

BitBoard positionLeadingOne(BitBoard b)
{
    int lz = __builtin_clzll((uint64_t)b);

    return (63 - lz);
}