#include "bitboard.h"
#include "primitives.h"

#pragma once

int rankFinder(BitBoard b);
int fileFinder(BitBoard b);

BitBoard ManualBishopAttacks(Square bishop, BitBoard occupancy);

BitBoard Diagonal(Square sq);
BitBoard AntiDiagonal(Square sq);
BitBoard Rank(Square sq);
BitBoard File(Square sq);
