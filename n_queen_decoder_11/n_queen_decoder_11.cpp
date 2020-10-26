// n_queen_decoder_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "L_Q_xy.h"
#include <fstream>
int main(int argc, const char* argv[])
{
	if (3 == argc)
	{
		std::ifstream input(argv[2]);
		std::string header;
		input >> header;
		if ("SAT" != header)
		{
			std::cout << "not a satisifing intepratation.";
			return 0;
		}
		else
		{
			int n_queen = atoi(argv[1]);
			int n_vars = n_queen * n_queen;

			auto onNewLite = [n_queen](int code)-> Literal* { return new L_Q_xy(code, n_queen, n_queen); };
			Clause cls;
			if (!ParseIter(input, onNewLite, cls))
			{
				std::cout << "not able to interprete!!!";
				return 0;
			}
			else
			{
				cls.Dump(std::cout);
				return 1;
			}
		}
	}
	else
	{
		std::cout << "n_queen_decoder_11 <number of queen> <interpretation file>" << std::endl;
		return 0;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
