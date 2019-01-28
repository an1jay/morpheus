#include "bitboard.h"
#include "constants.h"
#include "slidingattacks.h"
#include <iostream>


BitBoard bishopAttacks(const BitBoard b) {
    int bishop_rank = rankFinder(b);
    int bishop_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        BitBoard test_bb = (BitBoard)1 << i ; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if (abs(test_rank - bishop_rank) == abs(test_file - bishop_file)) { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b ;
}

BitBoard rookAttacks(const BitBoard b) {
    int rook_rank = rankFinder(b);
    int rook_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        BitBoard test_bb = (BitBoard)1 << i ; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ((test_rank == rook_rank) | (test_file == rook_file)){ // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b ;
}

BitBoard knightAttacks(const BitBoard b) {
    int knight_rank = rankFinder(b);
    int knight_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        BitBoard test_bb = (BitBoard)1 << i ; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        int abs_rank_diff = abs(knight_rank - test_rank);
        int abs_file_diff = abs(knight_file - test_file);
        if (((abs_rank_diff == 1) && (abs_file_diff == 2)) | ((abs_rank_diff == 2) && (abs_file_diff == 1))) { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b ;
}

BitBoard queenAttacks(const BitBoard b) {
    return bishopAttacks(b) | rookAttacks(b) ;
}

BitBoard kingAttacks(const BitBoard b) {
    int king_rank = rankFinder(b);
    int king_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        BitBoard test_bb = (BitBoard)1 << i ; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ((abs(king_rank - test_rank) <= 1) && (abs(king_file - test_file) <= 1)) { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b ;
}

BitBoard pawnAttacks(const BitBoard b, const Color c) {
    int pawn_rank = rankFinder(b);
    int pawn_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        BitBoard test_bb = (BitBoard)1 << i ; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ((abs(test_file - pawn_file) == 1) && (test_rank - pawn_rank == (int)c)) { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b ;
}

BitBoard pawnMoves(const BitBoard b, const Color c) {
    int pawn_rank = rankFinder(b);
    int pawn_file = fileFinder(b);
    BitBoard attacks = 0;
    for (BitBoard i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        BitBoard test_bb = (BitBoard)1 << i ; // generate a bitboard with a value in one square
        int test_rank = rankFinder(test_bb);
        int test_file = fileFinder(test_bb);
        if ( ( (pawn_rank == 3.5 - 2.5*(int)c) && (pawn_file == test_file) && (test_rank - pawn_rank == 2*(int)c) ) 
                    | ((pawn_file == test_file) && (test_rank - pawn_rank == (int)c)) ) { // see if piece attacks this square
            attacks = attacks | test_bb;
        }
    }
    return attacks & ~b ;
}

int rankFinder(BitBoard b) {
    int n = 0;
    // std::cout << "rank test " << ((b >> (8*n)) & BB_Rank1) << std::endl;
    while (((b >> (8*n)) & BB_Rank1) == 0) {
        n++;
    };
    // std::cout << "rank " << n << std::endl ;
    return n;
}

int fileFinder(BitBoard b) {
    int n = 0;
    // std::cout << "file test " << ((b >> n) & BB_FileA) << std::endl;
    while (((b >> n) & BB_FileA) == 0) {
        n++;
        // std::cout << "file test " << ((b >> n) & BB_FileA) << std::endl;
    };   
    // std::cout << "file " << n << std::endl ;
    return n;
}