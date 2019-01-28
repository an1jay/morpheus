#include "bitboard.h"
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;

	std::cout << "Better print" << std::endl;
	betterPrettyPrint(BB_FileA);
	std::cout << "Pretty print" << std::endl;
	prettyPrint(BB_FileA);

	std::cout << std::endl;
	binaryPrint(BB_FileA);
	std::cout << std::endl;

	boardPrint(BB_FileA);
}