// sudoku_decoder_12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "L_SKU_ijx.h"
int main(int argc, const char* argv[])
{
	if (3 == argc)
	{
		std::ifstream input_src(argv[1]);
		std::ifstream input_res(argv[2]);
		std::string header;
		input_res >> header;
		if ("SAT" != header)
		{
			std::cout << "not a satisifing intepratation.";
			return 0;
		}
		else
		{
			auto onNewLite = [](int code)-> Literal*
									{
										if (code > 0)
											return new L_SKU_ijx(code);
										else
											return NULL;
									};
			char grid_vis[9*9];
			SudokuGrid grid_log;
			Clause cls;

			if (!ParseIter(input_res, onNewLite, cls)
				|| !grid_log.Initialize(input_src, grid_vis))
			{
				std::cout << "not able to interprete!!!";
				return 0;
			}
			else
			{
				const std::list<const Literal*>& lits = cls.cnfLiterals();
				for (auto it_l = lits.begin()
					; it_l != lits.end()
					; it_l ++)
				{
					const L_SKU_ijx* ijx = static_cast<const L_SKU_ijx*>(*it_l);
					if (ijx->m_val)
					{
						char x = ijx->m_x + '0';
						grid_vis[ijx->m_r * 9 + ijx->m_c] = x;
					}
				}

				for (int i_y = 0; i_y < 9; i_y ++)
				{
					for (int i_x = 0; i_x < 9; i_x ++)
					{
						std::cout << grid_vis[i_y * 9 + i_x] << " ";
					}
					std::cout << std::endl;
				}
				return 1;
			}
		}
	}
	else
	{
		std::cout << "n_queen_decoder_11 <sudoku file> <interpretation file>" << std::endl;
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
