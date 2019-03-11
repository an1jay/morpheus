#include "primitives.h"

#pragma once

typedef uint_fast64_t BitBoard;

void BBbinaryPrint(BitBoard b); // Prints the bitboard as a binary number
void BBboardPrint(BitBoard b);  // Prints the bitboard as a chess board

bool BBoccupied(const BitBoard b, const Square sq); // Checks whether the square s is occupied on the bitboard b
BitBoard BBgenerate(const Square sq);               // Generates a bitboard with the square bit set to one
int BBcount(const BitBoard b);                      // Returns number of occupancies
BitBoard BBreverse(const BitBoard b);               // Reverse the bitboard
int BBfindMSB(const BitBoard b);
BitBoard BBpopMSB(const BitBoard b);

constexpr BitBoard BB_AllSquares = ~0;
constexpr BitBoard BB_NoSquares = 0;

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

constexpr BitBoard BB_Edges = BB_FileA | BB_FileH | BB_Rank1 | BB_Rank8;
constexpr BitBoard BB_NoEdges = ~BB_Edges;
constexpr BitBoard BB_EdgeArray[4] = {BB_FileA, BB_FileH, BB_Rank1, BB_Rank8};
