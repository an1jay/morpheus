#include "bitboard.h"
#include <iostream>

int main(int argc, char *argv[])
{

    std::cout << "Pretty print" << std::endl;
    prettyPrint(BB_Rank1);

    std::cout << std::endl;
    binaryPrint(BB_Rank1);
    std::cout << std::endl;

    boardPrint(BB_Rank1);
}