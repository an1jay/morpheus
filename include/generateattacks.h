#include "bitboard.h"
#include <iostream>

#pragma once

int fileFinder(BitBoard b);
int rankFinder(BitBoard b);
BitBoard bishopAttacksMask(const BitBoard b);
BitBoard rookAttacksMask(const BitBoard b);
BitBoard knightAttacks(const BitBoard b);
BitBoard kingAttacks(const BitBoard b);
BitBoard queenAttacksMask(const BitBoard b);
BitBoard pawnAttacks(const BitBoard b, const Color c);
BitBoard pawnMoves(const BitBoard b, const Color c);
