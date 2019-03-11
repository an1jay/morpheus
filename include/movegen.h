#include "bitboard.h"
#include "primitives.h"

#pragma once

int rankFinder(BitBoard b);
int fileFinder(BitBoard b);

BitBoard ManualBishopAttacks(const Square bishop, const BitBoard occupancy);
BitBoard ManualRookAttacks(const Square rook, const BitBoard occupancy);

BitBoard Diagonal(Square sq);
BitBoard AntiDiagonal(Square sq);
BitBoard Rank(Square sq);
BitBoard File(Square sq);

int rankFromSq(Square sq);
int fileFromSq(Square sq);

BitBoard pawnAttacks(Square sq, BitBoard occ, Color c);
