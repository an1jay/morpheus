#include "bitboard.h"
#include "primitives.h"
#include "slidingattacks.h"
#include <iostream>

int main()
{

	std::cout << "Pretty print" << std::endl;
	// prettyPrint(BB_Rank1);

	BitBoard test = generateBitBoard(Square::SQ_B2) ;

	std::cout << std::endl;
	binaryPrint(test);
	std::cout << std::endl;

	boardPrint(test);

	std::cout << "knight attacks" << std::endl ;
	boardPrint(knightAttacks(test));


	std::cout << "black pawn moves" << std::endl ;
	boardPrint(pawnMoves(test, Color::COLOR_BLACK));

	std::cout << "white pawn Moves" << std::endl ;
	boardPrint(pawnMoves(test, Color::COLOR_WHITE));


	
}