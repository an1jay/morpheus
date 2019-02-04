#include "bitboard.h"
#include "primitives.h"

#pragma once

class Magics
{
  public:
    Magics();
    BitBoard AttackFor(Square sq, BitBoard occupancy, PieceType PT) const;

  private:
    void initBishops();
    void initRooks();
    const int shift = 9;

    BitBoard BishopMagics[64];
    BitBoard RookMagics[64];

    BitBoard *BishopMagicAttacks;
    BitBoard *RookMagicAttacks;
};

BitBoard genRand();
// BitBoard popLeadingOne(BitBoard b);
// int positionLeadingOne(BitBoard b);

BitBoard *permuteBishopOccupancy(BitBoard b);
void AppendBishOcc(BitBoard b, BitBoard *arr, int *count);
