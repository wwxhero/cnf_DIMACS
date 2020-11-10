// n_Latinsqr_encoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "L_Latin_rcx.h"
void Permutation(int n_squares, Formula& fla)
{
	//for every row is a permuatation of the numbers from N
	Clause cls_cmmt("1. Each row and column is a permuatation!!!");
	fla.Add(cls_cmmt);

	Clause cls_cmmt_11("1.1 Each cell has number allocated!!!");
	fla.Add(cls_cmmt_11);
	for (int r = 0; r < n_squares; r ++)
	{
		for (int c = 0; c < n_squares; c ++)
		{
			Clause cls;
			for (int x = 0; x < n_squares; x ++)
			{
				Literal* rcx = new L_Latin_rcx(n_squares, r, c, x, true);
				cls.Add(rcx);
			}
			fla.Add(cls);
		}
	}

	Clause cls_cmmt_12("1.2 Each row is a permutation!!!");
	fla.Add(cls_cmmt_12);
	for (int r = 0; r < n_squares; r ++)
	{
		int c_1_end = n_squares - 1;
		int c_2_end = n_squares;
		for (int c_1 = 0; c_1 < c_1_end; c_1 ++)
		{
			for (int c_2 = c_1 + 1; c_2 < c_2_end; c_2 ++)
			{
				for (int x = 0; x < n_squares; x ++)
				{
					Clause cls;
					Literal* neg_rc1x = new L_Latin_rcx(n_squares, r, c_1, x, false);
					Literal* neg_rc2x = new L_Latin_rcx(n_squares, r, c_2, x, false);
					cls.Add(neg_rc1x);
					cls.Add(neg_rc2x);
					fla.Add(cls);
				}
			}
		}
	}

	Clause cls_cmmt_13("1.3 Each column is a permuatation!!!");
	fla.Add(cls_cmmt_13);
	for (int c = 0; c < n_squares; c ++)
	{
		int r_1_end = n_squares - 1;
		int r_2_end = n_squares;
		for (int r_1 = 0; r_1 < r_1_end; r_1 ++)
		{
			for (int r_2 = r_1 + 1; r_2 < r_2_end; r_2 ++)
			{
				for (int x = 0; x < n_squares; x ++)
				{
					Clause cls;
					Literal* neg_r1cx = new L_Latin_rcx(n_squares, r_1, c, x, false);
					Literal* neg_r2cx = new L_Latin_rcx(n_squares, r_2, c, x, false);
					cls.Add(neg_r1cx);
					cls.Add(neg_r2cx);
					fla.Add(cls);
				}
			}
		}
	}
}

void XstarXeqX(int n_squares, Formula& fla)
{
	//x * x = x for x in {0, ..., n-1}
	Clause cls_cmmt("x * x = x");
	fla.Add(cls_cmmt);
	for (int x = 0; x < n_squares; x ++)
	{
		Clause cls;
		Literal* l_xxx = new L_Latin_rcx(n_squares, x, x, x, true);
		cls.Add(l_xxx);
		fla.Add(cls);
	}
}

void Steins3rdLaw(int n_squares, Formula& fla)
{
	//(x*y) * (y*x) = y
	Clause cls_cmmt("(x*y) * (y*x) = y");
	fla.Add(cls_cmmt);
	int x_end = n_squares - 1;
	int y_end = n_squares;
	for (int x = 0; x < x_end; x ++)
	{
		for (int y = 0; y < y_end; y ++)
		{
			for (int xy = 0; xy < n_squares; xy ++)
			{
				for (int yx = 0; yx < n_squares; yx ++)
				{
					Clause cls;
					Literal* neg_xy = new L_Latin_rcx(n_squares, x, y, xy, false);
					Literal* neg_yx = new L_Latin_rcx(n_squares, y, x, yx, false);
					Literal*  xy_yx = new L_Latin_rcx(n_squares, xy, yx, y, true);
					cls.Add(neg_xy);
					cls.Add(neg_yx);
					cls.Add(xy_yx);
					fla.Add(cls);
				}
			}
		}
	}

}

using namespace std;
int main(int argc, const char* argv[])
{
	if (2 != argc)
	{
		cout << "n_Latinsqr_encoder <number of squares>" << endl;
		return 0;
	}
	else
	{
		int n_latin = atoi(argv[1]);
		Formula fla(n_latin * n_latin * n_latin);
		stringstream cmt;
		cmt << "c Latin square with " << n_latin << "x" << n_latin <<" squares!!!";
		cout << cmt.str() << endl;
		Permutation(n_latin, fla);
		XstarXeqX(n_latin, fla);
		Steins3rdLaw(n_latin, fla);
		fla.Dump(cout);
		return 1;
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
