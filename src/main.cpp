#include "bitboard.h"
#include "slidingattacks.h"
#include <iostream>

int main()
{

	std::cout << "Pretty print" << std::endl;
	// prettyPrint(BB_Rank1);

	BitBoard test = (BitBoard)1<<45 ;

	std::cout << std::endl;
	binaryPrint(test);
	std::cout << std::endl;

	boardPrint(test);

	std::cout << "bishop attacks" << std::endl ;
	boardPrint(bishopAttacks(test));
	
}