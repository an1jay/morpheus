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
BitBoard popLeadingOne(BitBoard b);

void permuteBishopOccupancy(BitBoard b);
void appendBishOcc(BitBoard b, BitBoard *arr, int count);
void NewAppendBishOcc(BitBoard b, BitBoard *arr, int count);