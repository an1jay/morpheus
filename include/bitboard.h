#include "primitives.h"

#pragma once

typedef uint64_t BitBoard;

constexpr BitBoard BB_AllSquares = ~BitBoard(0);

constexpr BitBoard BB_FileA = 0x0101010101010101ULL;
constexpr BitBoard BB_FileB = BB_FileA << 1;
constexpr BitBoard BB_FileC = BB_FileA << 2;
constexpr BitBoard BB_FileD = BB_FileA << 3;
constexpr BitBoard BB_FileE = BB_FileA << 4;
constexpr BitBoard BB_FileF = BB_FileA << 5;
constexpr BitBoard BB_FileG = BB_FileA << 6;
constexpr BitBoard BB_FileH = BB_FileA << 7;

constexpr BitBoard BB_Rank1 = 0xFF;
constexpr BitBoard BB_Rank2 = BB_Rank1 << (8 * 1);
constexpr BitBoard BB_Rank3 = BB_Rank1 << (8 * 2);
constexpr BitBoard BB_Rank4 = BB_Rank1 << (8 * 3);
constexpr BitBoard BB_Rank5 = BB_Rank1 << (8 * 4);
constexpr BitBoard BB_Rank6 = BB_Rank1 << (8 * 5);
constexpr BitBoard BB_Rank7 = BB_Rank1 << (8 * 6);
constexpr BitBoard BB_Rank8 = BB_Rank1 << (8 * 7);