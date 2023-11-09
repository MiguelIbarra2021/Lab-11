#include "Huffman_Algorithm.h"	// Git

std::string Get_Input();

int main()
{
	Huffman_Algorithm bt;

	bt.Encode_Word(Get_Input());
	bt.Decode_Word(Get_Input());
}

std::string Get_Input()
{
	std::string input = "";

	std::cout << "\n\nPlease type requested input below:";
	std::cout << "\n-";

	std::getline(std::cin, input);

	return input;
}
