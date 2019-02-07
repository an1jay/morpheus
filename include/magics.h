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
    const static int BishopMax = 512;
    const static int RookMax = 4096;

    BitBoard BishopMagics[64];
    BitBoard RookMagics[64];

    BitBoard BishopMagicAttacks[64][BishopMax];
    BitBoard RookMagicAttacks[64][1];
};

BitBoard genRand();
// BitBoard popLeadingOne(BitBoard b);
// int positionLeadingOne(BitBoard b);

void permuteBishopOccupancy(BitBoard b, BitBoard *arr);
void AppendBishOcc(BitBoard b, BitBoard *arr, int *count);
