#include "bitboard.h"
#include "constants.h"
#include "slidingattacks.h"
#include <bitset>
#include <iostream>


BitBoard bishopAttacks(BitBoard b) {
    int bishop_rank = rankFinder(b);
    int bishop_file = fileFinder(b);
    for (int i=0 ; i<NUM_SQUARES_BOARD ; i++) {
        rank
    }

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