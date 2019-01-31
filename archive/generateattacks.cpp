#include "generateattacks.h"
#include "bitboard.h"
#include "constants.h"
#include <iostream>

BitBoard bishopAttacksMask(const BitBoard b)
{
    int bishop_rank = rankFinder(b);
    int bishop_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        BitBoard test_bb = (BitBoard)1 << i; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if (abs(test_rank - bishop_rank) == abs(test_file - bishop_file))
        { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b;
}

BitBoard rookAttacksMask(const BitBoard b)
{
    int rook_rank = rankFinder(b);
    int rook_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        BitBoard test_bb = (BitBoard)1 << i; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ((test_rank == rook_rank) | (test_file == rook_file))
        { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b;
}

BitBoard knightAttacks(const BitBoard b)
{
    int knight_rank = rankFinder(b);
    int knight_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        BitBoard test_bb = (BitBoard)1 << i; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        int abs_rank_diff = abs(knight_rank - test_rank);
        int abs_file_diff = abs(knight_file - test_file);
        if (((abs_rank_diff == 1) && (abs_file_diff == 2)) | ((abs_rank_diff == 2) && (abs_file_diff == 1)))
        { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b;
}

BitBoard queenAttacksMask(const BitBoard b)
{
    return bishopAttacksMask(b) | rookAttacksMask(b);
}

BitBoard kingAttacks(const BitBoard b)
{
    int king_rank = rankFinder(b);
    int king_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        BitBoard test_bb = (BitBoard)1 << i; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ((abs(king_rank - test_rank) <= 1) && (abs(king_file - test_file) <= 1))
        { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b;
}

BitBoard pawnAttacks(const BitBoard b, const Color c)
{
    int pawn_rank = rankFinder(b);
    int pawn_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        BitBoard test_bb = (BitBoard)1 << i; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ((abs(test_file - pawn_file) == 1) && (test_rank - pawn_rank == (int)c))
        { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b;
}

BitBoard pawnMoves(const BitBoard b, const Color c)
{
    int pawn_rank = rankFinder(b);
    int pawn_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i = 0; i < NUM_SQUARES_BOARD; i++)
    {
        BitBoard test_bb = (BitBoard)1 << i; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if (((pawn_rank == 3.5 - 2.5 * (int)c) && (pawn_file == test_file) && (test_rank - pawn_rank == 2 * (int)c)) | ((pawn_file == test_file) && (test_rank - pawn_rank == (int)c)))
        { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b;
}

int rankFinder(BitBoard b)
{
    int n = 0;
    // std::cout << "rank test " << ((b >> (8*n)) & BB_Rank1) << std::endl;
    while (((b >> (8 * n)) & BB_Rank1) == 0)
    {
        n++;
    };
    // std::cout << "rank " << n << std::endl ;
    return n;
}

int fileFinder(BitBoard b)
{
    int n = 0;
    // std::cout << "file test " << ((b >> n) & BB_FileA) << std::endl;
    while (((b >> n) & BB_FileA) == 0)
    {
        n++;
        // std::cout << "file test " << ((b >> n) & BB_FileA) << std::endl;
    };
    // std::cout << "file " << n << std::endl ;
    return n;
}

void generateMovesArray(Piece p)
{
    BitBoard piecePos;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        piecePos = generateBB((Square)sq);
        switch (p)
        {
        case Piece::W_BISHOP:
            std::cout << (uint64_t)bishopAttacksMask(piecePos) << "ULL, ";
            if ((sq + 1) % 8 == 0)
            {
                std::cout << std::endl;
            }
            break;

        case Piece::W_KNIGHT:
            std::cout << (uint64_t)knightAttacks(piecePos) << "ULL, ";
            if ((sq + 1) % 8 == 0)
            {
                std::cout << std::endl;
            }
            break;

        case Piece::W_KING:
            std::cout << (uint64_t)kingAttacks(piecePos) << "ULL, ";
            if ((sq + 1) % 8 == 0)
            {
                std::cout << std::endl;
            }
            break;

        case Piece::W_ROOK:
            std::cout << (uint64_t)rookAttacksMask(piecePos) << "ULL, ";
            if ((sq + 1) % 8 == 0)
            {
                std::cout << std::endl;
            }
            break;

        case Piece::W_QUEEN:
            std::cout << (uint64_t)queenAttacksMask(piecePos) << "ULL, ";
            if ((sq + 1) % 8 == 0)
            {
                std::cout << std::endl;
            }
            break;

        default:
            break;
        }
    }
}

void testMoves(Square sq)
{
    std::cout << "Square " << (int)sq << std::endl;
    std::cout << "Knight Moves" << std::endl;
    BBboardPrint(BlankKnightMoves[(int)sq]);
    std::cout << "Bishop Moves" << std::endl;
    BBboardPrint(BlankBishopMoves[(int)sq]);
    std::cout << "Rook Moves" << std::endl;
    BBboardPrint(BlankRookMoves[(int)sq]);
    std::cout << "Queen Moves" << std::endl;
    BBboardPrint(BlankQueenMoves[(int)sq]);
    std::cout << "King Moves" << std::endl;
    BBboardPrint(BlankKingMoves[(int)sq]);
}