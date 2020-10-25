// n_queen_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "logicBase.h"

class P_Q_xy : public Proposition
{
public:
	P_Q_xy(int x, int y, int nX, int nY, bool val)
		: Proposition(val)
		, m_x(x)
		, m_y(y)
		, m_nX(nX)
		, m_nY(nY)
	{
	}

	virtual Literal encode() const
	{
		//to encode proposition into DIMACS literal
		int code = m_x * m_nY + m_y + 1;
		Literal lit(code, m_val, m_nX, m_nY);
		return lit;
	}

private:
	const int m_x;
	const int m_y;
	const int m_nX;
	const int m_nY;
};


void EveryColumnExistsQueen(int n_queen, Formula& fla)
{
	Clause cls_cmmt("Every colomn exists a queen");
	fla.Add(cls_cmmt);
	int n_col = n_queen;
	for (int x = 0; x < n_col; x ++)
	{
		Clause cls_x;
		int n_row = n_queen;
		for (int y = 0; y < n_row; y ++)
		{
			P_Q_xy qxy(x, y, n_row, n_col, true);
			cls_x.Add(qxy.encode());
		}
		fla.Add(cls_x);
	}
}

void EveryRowExistsQueen(int n_queen, Formula& fla)
{
	Clause cls_cmmt("Every row exists a queen");
	fla.Add(cls_cmmt);
	int n_row = n_queen;
	for (int y = 0; y < n_row; y ++)
	{
		Clause cls_y;
		int n_col = n_queen;
		for (int x = 0; x < n_col; x ++)
		{
			P_Q_xy qxy(x, y, n_col, n_row, true);
			cls_y.Add(qxy.encode());
		}
		fla.Add(cls_y);
	}
}

void No2QueensOnSameColomn(int n_queen, Formula& fla)
{
	Clause cls_cmmt("No 2 queens on the same colomn");
	fla.Add(cls_cmmt);
	int n_col = n_queen;
	int n_row = n_queen;
	for (int x = 0; x < n_col; x ++)
	{
		for (int y = 0; y < n_row - 1; y ++)
		{
			P_Q_xy neg_qxy_p(x, y, n_col, n_row, false);
			Literal neg_qxy_l = neg_qxy_p.encode();
			for (int y2 = y + 1; y2 < n_row; y2 ++)
			{
				Clause cls_xyy2;
				P_Q_xy neg_qxy2_p(x, y2, n_col, n_row, false);
				cls_xyy2.Add(neg_qxy_l);
				cls_xyy2.Add(neg_qxy2_p.encode());
				fla.Add(cls_xyy2);
			}
		}
	}
}

void No2QueensOnSameRow(int n_queen, Formula& fla)
{
	Clause cls_cmmt("No 2 queens on the same row");
	fla.Add(cls_cmmt);
	int n_col = n_queen;
	int n_row = n_queen;
	for (int y = 0; y < n_row; y ++)
	{
		for (int x = 0; x < n_col - 1; x ++)
		{
			P_Q_xy neg_qxy_p(x, y, n_col, n_row, false);
			Literal neg_qxy_l = neg_qxy_p.encode();
			for (int x2 = x + 1; x2 < n_col; x2 ++)
			{
				Clause cls_xx2y;
				P_Q_xy neg_qx2y_p(x2, y, n_col, n_row, false);
				cls_xx2y.Add(neg_qxy_l);
				cls_xx2y.Add(neg_qx2y_p.encode());
				fla.Add(cls_xx2y);
			}
		}
	}
}

void No2QueensOnSameDiagnol(int n_queen, Formula& fla)
{
	Clause cls_cmmt("No 2 queens on the same diagnal");
	fla.Add(cls_cmmt);
	int n_col = n_queen;
	int n_row = n_queen;
	for (int x1 = 0; x1 < n_col - 1; x1 ++)
	{
		for (int y1 = 0; y1 < n_row; y1 ++)
		{
			P_Q_xy neg_qx1y1_p(x1, y1, n_col, n_row, false);
			Literal neg_qx1y1_l = neg_qx1y1_p.encode();
			int x2 = x1 + 1;
			int y2;
			int offset[] = {-1, 1};
			for (int i_offset = 0; i_offset < 2; i_offset ++)
			{
				y2 = y1 + offset[i_offset];
				bool valid_y2 = (-1 < y2 && y2 < n_col);
				if (valid_y2)
				{
					P_Q_xy neg_qx2y2_p(x2, y2, n_col, n_row, false);
					Literal neg_qx2y2_l = neg_qx2y2_p.encode();
					Clause cls_x1y1_x2y2;
					cls_x1y1_x2y2.Add(neg_qx1y1_l);
					cls_x1y1_x2y2.Add(neg_qx2y2_l);
					fla.Add(cls_x1y1_x2y2);
				}
			}
		}
	}
}

int main(int argc, const char* argv[])
{
	if (2 == argc)
	{
		int n_queen = atoi(argv[1]);
		Formula fla(n_queen * n_queen);
		std::stringstream cmt;
		cmt << "c Put "
			<< n_queen
			<< " queen(s) on to "
			<< n_queen
			<< " x "
			<< n_queen
			<< " board";
		std::cout << cmt.str() << std::endl;
		EveryRowExistsQueen(n_queen, fla);
		EveryColumnExistsQueen(n_queen, fla);
		No2QueensOnSameRow(n_queen, fla);
		No2QueensOnSameColomn(n_queen, fla);
		No2QueensOnSameDiagnol(n_queen, fla);
		fla.Dump(std::cout);
		return 1;
	}
	else
	{
		std::cout << "n_queen_11 <number of queens>" << std::endl;
		return 0;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to Add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to Add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
