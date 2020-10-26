// sudoku_encoder_12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "L_SKU_ijx.h"
void EachCellContainsOneDigit(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("1. Each cell contains at least one digit.");
	formula.Add(cls_cmmt);
	const std::list<SudokuGrid::Cell>& cells = grid.emptyCells();
	for (auto it_cell = cells.begin()
		; it_cell != cells.end()
		; it_cell ++)
	{
		const std::list<int>& X = grid.fullX();
		Clause cls;
		for (auto it_x = X.begin()
			; it_x != X.end()
			; it_x ++)
		{
			Literal* ijx = new L_SKU_ijx(it_cell->row_i, it_cell->col_i, *it_x, true);
			cls.Add(ijx);
		}
		formula.Add(cls);
	}
}

void EachCellContainsNoMoreThanOneDigit(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("2. Each cell contains at most one digit.");
	formula.Add(cls_cmmt);
	const std::list<SudokuGrid::Cell>& cells = grid.emptyCells();
	for (auto it_cell = cells.begin()
		; it_cell != cells.end()
		; it_cell ++)
	{
		const std::list<int>& X = grid.fullX();
		auto it_x_1_end = X.end();
		auto it_x_2_end = it_x_1_end;
		it_x_1_end--;
		for (auto it_x_1 = X.begin()
			; it_x_1 != it_x_1_end
			; it_x_1 ++)
		{
			auto it_x_2 = it_x_1; it_x_2 ++;
			for (
				; it_x_2 != it_x_2_end
				; it_x_2 ++)
			{
				Literal* neg_ijx1 = new L_SKU_ijx(it_cell->row_i, it_cell->col_i, *it_x_1, false);
				Literal* neg_ijx2 = new L_SKU_ijx(it_cell->row_i, it_cell->col_i, *it_x_2, false);
				Clause cls;
				cls.Add(neg_ijx1);
				cls.Add(neg_ijx2);
				formula.Add(cls);
			}
		}
	}
}

typedef const std::list<SudokuGrid::Cell>& (SudokuGrid::*GetGroupCells)(int id) const;

void EachLineContainsEveryDigitOnce(const SudokuGrid& grid, GetGroupCells funcGetGroup, Formula& formula)
{
	auto X = grid.fullX();
	for (auto it_x = X.begin()
		; it_x != X.end()
		; it_x ++)
	{
		for (int id_g = 0; id_g < 9; id_g ++)
		{
			auto cells_l = (grid.*(funcGetGroup))(id_g);
			auto ij2_end = cells_l.end();
			auto ij_end = ij2_end; ij_end --;
			for (auto it_ij = cells_l.begin()
				; it_ij != ij_end
				; it_ij ++)
			{
				auto it_ij2 = it_ij; it_ij2 ++;
				for (
					; it_ij2 != ij2_end
					; it_ij2 ++)
				{
					Literal* neg_ijx = new L_SKU_ijx(it_ij->row_i, it_ij->col_i, *it_x, false);
					Literal* neg_ij2x = new L_SKU_ijx(it_ij2->row_i, it_ij2->col_i, *it_x, false);
					Clause cls;
					cls.Add(neg_ijx);
					cls.Add(neg_ij2x);
					formula.Add(cls);
				}
			}
		}
	}
}

void EachRowContainsEveryDigitOnce(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("3. Each row contains every digit at most once.");
	formula.Add(cls_cmmt);
	GetGroupCells proc = &SudokuGrid::emptyCells_r;
	EachLineContainsEveryDigitOnce(grid, proc, formula);
}

void EachColumnContainsEveryDigitOnce(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("4. Each column contains every digit at most once.");
	formula.Add(cls_cmmt);
	GetGroupCells proc = &SudokuGrid::emptyCells_c;
	EachLineContainsEveryDigitOnce(grid, proc, formula);
}

void EachGridContainsEveryDigitOnce(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("5. Each grid contains every digit at most once.");
	formula.Add(cls_cmmt);
	GetGroupCells proc = &SudokuGrid::emptyCells_g;
	EachLineContainsEveryDigitOnce(grid, proc, formula);
}

int main(int argc, const char* argv[])
{
    if (2 == argc)
    {
    	const char* filepath = argv[1];
    	std::ifstream sudoku_in(filepath);
    	SudokuGrid grid;
    	if (grid.Initialize(sudoku_in))
    	{
    		Formula formula(1000);
    		EachCellContainsOneDigit(grid, formula);
    		EachCellContainsNoMoreThanOneDigit(grid, formula);
    		EachRowContainsEveryDigitOnce(grid, formula);
    		EachColumnContainsEveryDigitOnce(grid, formula);
    		EachGridContainsEveryDigitOnce(grid, formula);
    		formula.Dump(std::cout);
    	}
    	else
    	{
    		std::cout << "not an available sudoku file!!!" << std::endl;
    		return 0;
    	}
    }
    else
    {
    	std::cout << "sudoku_encoder_12 <sudoku file>" << std::endl;
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
