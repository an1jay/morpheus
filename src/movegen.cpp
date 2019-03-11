#include "movegen.h"
#include "bitboard.h"
#include "constants.h"
#include "position.h"
#include "primitives.h"

BitBoard ManualBishopAttacks(const Square bishop, const BitBoard occupancy)
{
    BitBoard diagonal = Diagonal(bishop);
    BitBoard antidiagonal = AntiDiagonal(bishop);
    BitBoard piecePos = BBgenerate(bishop);
    BitBoard OccupiedInDiagonal = occupancy & diagonal;
    BitBoard OccupiedInAntiDiagonal = occupancy & antidiagonal;
    //diagonals
    BitBoard diagAttacks = ((OccupiedInDiagonal - 2 * piecePos) ^ BBreverse((BBreverse(OccupiedInDiagonal) - 2 * BBreverse(piecePos)))) & diagonal;
    //anti diagonals
    BitBoard antidiagAttacks = ((OccupiedInAntiDiagonal - 2 * piecePos) ^ BBreverse((BBreverse(OccupiedInAntiDiagonal) - 2 * BBreverse(piecePos)))) & antidiagonal;
    return diagAttacks | antidiagAttacks;
}

BitBoard ManualRookAttacks(Square rook, BitBoard occupancy)
{
    BitBoard rank = Rank(rook);
    BitBoard file = File(rook);
    BitBoard piecePos = BBgenerate(rook);
    BitBoard OccupiedInRank = occupancy & rank;
    BitBoard OccupiedInFile = occupancy & file;
    //ranks
    BitBoard rankAttacks = ((OccupiedInRank - 2 * piecePos) ^ BBreverse((BBreverse(OccupiedInRank) - 2 * BBreverse(piecePos)))) & rank;
    //files
    BitBoard fileAttacks = ((OccupiedInFile - 2 * piecePos) ^ BBreverse((BBreverse(OccupiedInFile) - 2 * BBreverse(piecePos)))) & file;
    return rankAttacks | fileAttacks;
}

BitBoard File(Square sq)
{
    int sq_file = fileFinder(BBgenerate(sq));
    BitBoard result = BB_NoSquares;
    for (int i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        if (fileFinder(BBgenerate((Square)i)) == sq_file)
        {
            result |= BBgenerate((Square)i);
        }
    }
    return result;
}

BitBoard Rank(Square sq)
{
    int sq_rank = rankFinder(BBgenerate(sq));
    BitBoard result = BB_NoSquares;
    for (int i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        if (rankFinder(BBgenerate((Square)i)) == sq_rank)
        {
            result |= BBgenerate((Square)i);
        }
    }
    return result;
}

BitBoard Diagonal(Square sq)
{
    int sq_file = fileFinder(BBgenerate(sq));
    int sq_rank = rankFinder(BBgenerate(sq));
    BitBoard result = BB_NoSquares;
    int test_file;
    int test_rank;
    for (int i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        test_file = fileFinder(BBgenerate((Square)i));
        test_rank = rankFinder(BBgenerate((Square)i));
        if ((test_rank - sq_rank == test_file - sq_file))
        {
            result |= BBgenerate((Square)i);
        }
    }
    return result;
}

BitBoard AntiDiagonal(Square sq)
{
    int sq_file = fileFinder(BBgenerate(sq));
    int sq_rank = rankFinder(BBgenerate(sq));
    BitBoard result = BB_NoSquares;
    int test_file;
    int test_rank;
    for (int i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        test_file = fileFinder(BBgenerate((Square)i));
        test_rank = rankFinder(BBgenerate((Square)i));

        if ((test_rank - sq_rank == sq_file - test_file))
        {
            result |= BBgenerate((Square)i);
        }
    }
    return result;
}

int rankFinder(BitBoard b)
{
    int n = 0;
    while (((b >> (8 * n)) & BB_Rank1) == 0)
        n++;
    return n;
}

int fileFinder(BitBoard b)
{
    int n = 0;
    while (((b >> n) & BB_FileA) == 0)
        n++;
    return n;
}

// from 0 to 7
int rankFromSq(Square sq)
{
    return (int)sq / NUM_FILES;
}

// from 0 to 7
int fileFromSq(Square sq)
{
    return (int)sq % NUM_RANKS;
}

BitBoard pawnAttacks(Square sq, BitBoard occ, Color c)
{
    BitBoard moves = BB_NoSquares;
    BitBoard BBsq = BBgenerate(sq);
    int sqrank = rankFromSq(sq);

    switch (c)
    {
    case Color::WHITE:

        if (((BBsq << 8) & occ) == 0)
        {
            moves ^= BBsq << 8;
            if ((((BBsq << 16) & occ) == 0) && sqrank == 1)

                moves ^= BBsq << 16;
        }

        if ((BBsq << 7) & occ & BB_Ranks[sqrank + 1]) // maybe BB_rank1 << 8*(sqrank)
            moves ^= BBsq << 7;

        if ((BBsq << 9) & occ & BB_Ranks[sqrank + 1])
            moves ^= BBsq << 9;

        break;
    case Color::BLACK:
        if (((BBsq >> 8) & occ) == 0)
        {
            moves ^= BBsq >> 8;
            if ((((BBsq >> 16) & occ) == 0) && sqrank == 6)
            {
                moves ^= BBsq >> 16;
            }
        }

        if ((BBsq >> 7) & occ & BB_Ranks[sqrank - 1])
            moves ^= BBsq >> 7;

        if ((BBsq >> 9) & occ & BB_Ranks[sqrank - 1])
            moves ^= BBsq >> 9;

        break;
    default:
        break;
    }
    return moves;
}