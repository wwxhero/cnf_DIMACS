// n_Latinsqr_decoder_13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include "L_Latin_rcx.h"
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
			int n_latin = atoi(argv[1]);

			auto onNewLite = [n_latin](int code)-> Literal* { return new L_Latin_rcx(code, n_latin); };

			Clause cls;
			if (!ParseIter(input, onNewLite, cls))
			{
				std::cout << "not able to interprete!!!";
				return 0;
			}
			else
			{
				std::cout << "Solution is:" << std::endl;
				int* grid = new int[n_latin*n_latin]{0};
				const std::list<const Literal*>& lits = cls.cnfLiterals();
				for (auto it_l = lits.begin()
					; it_l != lits.end()
					; it_l ++)
				{
					const L_Latin_rcx* l_rcx = static_cast<const L_Latin_rcx*>(*it_l);
					if (l_rcx->m_val)
						grid[l_rcx->m_r * n_latin + l_rcx->m_c] = l_rcx->m_x;
				}

				for (int i_y = 0; i_y < n_latin; i_y ++)
				{
					std::cout << "\t";
					for (int i_x = 0; i_x < n_latin; i_x ++)
					{
						printf("%2d ", grid[i_y * n_latin + i_x]);
					}
					std::cout << std::endl;
				}
				delete [] grid;
				return 1;
			}
		}
	}
	else
	{
		std::cout << "n_latin_decoder_11 <number of latins> <interpretation file>" << std::endl;
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
