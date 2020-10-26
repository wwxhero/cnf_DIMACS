// sudoku_encoder_12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void EachCellContainsOneDigit(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("1. Each cell contains at least one digit.");
	formula.Add(cls_cmmt);
	const std::list<int> Row = grid.Row();
	const std::list<int> Col = grid.Col();
	for(auto it_r = Row.begin()
		; it_r != Row.end()
		; it_r ++)
	{
		for(auto it_c = Col.begin()
			; it_c != Col.end()
			; it_c ++)
		{
			Clause cls;
			const std::list<int>& X = grid.fullX();
			for (auto it_x = X.begin()
				; it_x != X.end()
				; it_x ++)
			{
				Literal* ijx = new L_SKU_ijx(*it_r, *it_c, *it_x, true);
				cls.Add(ijx);
			}
			formula.Add(cls);
		}
	}
}

void EachCellContainsNoMoreThanOneDigit(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("2. Each cell contains at most one digit.");
	formula.Add(cls_cmmt);
	const std::list<int> Row = grid.Row();
	const std::list<int> Col = grid.Col();
	for(auto it_r = Row.begin()
		; it_r != Row.end()
		; it_r ++)
	{
		for(auto it_c = Col.begin()
			; it_c != Col.end()
			; it_c ++)
		{
			const std::list<int>& X = grid.fullX();
			auto it_x_2_end = X.end();
			auto it_x_1_end = it_x_2_end; it_x_1_end --;
			for (auto it_x_1 = X.begin()
				; it_x_1 < it_x_1_end
				; it_x_1 ++)
			{
				Literal* neg_ijx1 = new L_SKU_ijx(*it_r, *it_c, *it_x_1, false);
				auto it_x_2 = it_x_1; it_x_2 ++;
				for (
					; it_x_2 < it_x_2_end
					; it_x_2 ++)
				{
					Clause cls;
					Literal* neg_ijx2 = new L_SKU_ijx(*it_r, *it_c, *it_x_2, false);
					cls.Add(neg_ijx1);
					cls.Add(neg_ijx2);
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
	const std::list<int> Row = grid.Row();
	const std::list<int> Col = grid.Col();
	auto it_c_2_end = Col.end();
	auto it_c_1_end = it_c_2_end; it_c_1_end --;
	for(auto it_r = Row.begin()
		; it_r != Row.end()
		; it_r ++)
	{
		const std::list<int> X_r = grid.rowX(*it_r);
		for (auto it_x = X_r.begin()
			; it_x != X_r.end()
			; it_x ++)
		{
			for(auto it_c_1 = Col.begin()
			; it_c_1 != it_c_1_end
			; it_c_1 ++)
			{
				Literal* neg_ij1x = new L_SKU_ijx(*it_r, *it_c_1, *it_x, false);
				for (auto it_c_2 = it_c_1, it_c_2 ++
					; it_c_2 != Col.it_c_2_end
					; it_c_2 ++)
				{
					Literal* neg_ij2x = new L_SKU_ijx(*it_r, *it_c_2, *it_x, false);
					Clause cls;
					cls.Add(neg_ij1x);
					cls.Add(neg_ij2x);
					formula.Add(cls);
				}
			}
		}
	}
}

void EachColumnContainsEveryDigitOnce(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("4. Each column contains every digit at most once.");
	formula.Add(cls_cmmt);
	const std::list<int> Row = grid.Row();
	const std::list<int> Col = grid.Col();
	auto it_r_2_end = Row.end();
	auto it_r_1_end = it_r_2_end; it_r_1_end --;
	for(auto it_c = Col.begin()
		; it_c != Col.end()
		; it_c ++)
	{
		const std::list<int> X_c = grid.colX(*it_c);
		for (auto it_x = X_c.begin()
			; it_x != X_c.end()
			; it_x ++)
		{
			for(auto it_r_1 = Row.begin()
			; it_r_1 != it_r_1_end
			; it_r_1 ++)
			{
				Literal* neg_ij1x = new L_SKU_ijx(*it_r_1, *it_c,  *it_x, false);
				for (auto it_r_2 = it_r_1, it_r_2 ++
					; it_r_2 != Col.it_r_2_end
					; it_r_2 ++)
				{
					Literal* neg_ij2x = new L_SKU_ijx(*it_r_2, *it_c, *it_x, false);
					Clause cls;
					cls.Add(neg_ij1x);
					cls.Add(neg_ij2x);
					formula.Add(cls);
				}
			}
		}
	}
}

void EachGridContainsEveryDigitOnce(const SudokuGrid& grid, Formula& formula)
{
	Clause cls_cmmt("5. Each grid contains every digit at most once.");
	formula.Add(cls_cmmt);

	for (int i_g = 0; i_g < 3; i_g ++)
	{
		for (int j_g = 0; j_g < 3; j_g ++)
		{
			const std::list<int> Row_g = grid.subGridRow(i_g, j_g);
			const std::list<int> Col_g = grid.subGridCol(i_g, j_g);

		}
	}



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
    		Formula formula;
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
