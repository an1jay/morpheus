#include "bitboard.h"
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;

	prettyPrint(BB_Rank1);
	binaryPrint(BB_Rank1);
	boardPrint(BB_Rank1);
}