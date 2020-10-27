// pigeon_hold_10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <sstream>
#include "logicBase.h"

class L_PH_xy : public Literal
{
public:
	L_PH_xy(int i_pigeon, int n_pigeon, int i_hole, int n_hole, bool val)
		: Literal(val, i_pigeon * n_hole + i_hole + 1)
		, m_iPigeon(i_pigeon)
		, m_nPigeon(n_pigeon)
		, m_iHole(i_hole)
		, m_nHole(n_hole)
	{
	}
	virtual void Dump(std::ostream& outs) const override
	{
#ifdef _DEBUG
		if (m_val)
			outs << m_iPigeon << "_" << m_iHole;
		else
			outs << m_iPigeon << "_" << m_iHole << "'";
#else
		return Literal::Dump(outs);
#endif
	}
private:
	const int m_iPigeon;
	const int m_iHole;
	const int m_nPigeon;
	const int m_nHole;
};

inline void EveryPigeonInAhole(int n_pigeon, int n_hole, Formula& formula)
{
	Clause cmt("Every pigeon is in a hole");
	formula.Add(cmt);
	for (int i_pigeon = 0; i_pigeon < n_pigeon; i_pigeon++)
	{
		Clause p_inhole;
		for (int i_hole = 0; i_hole < n_hole; i_hole++)
		{
			p_inhole.Add(new L_PH_xy(i_pigeon, n_pigeon, i_hole, n_hole, true));
		}
		formula.Add(p_inhole);
	}
}

inline void NoHolesCanHoldMoreThanOnePigeon(int n_pigeon, int n_hole, Formula& formula)
{
	Clause cmt("No holes can hole more than one pigeon");
	formula.Add(cmt);
	for (int i_hole = 0; i_hole < n_hole; i_hole++)
	{
		for (int i_pigeon = 0; i_pigeon < n_pigeon - 1; i_pigeon++)
		{
			for (int i_pigeon2 = i_pigeon + 1; i_pigeon2 < n_pigeon; i_pigeon2++)
			{
				Literal* neg_p_h = new L_PH_xy(i_pigeon, n_pigeon, i_hole, n_hole, false);
				Literal* neg_p2_h = new L_PH_xy(i_pigeon2, n_pigeon, i_hole, n_hole, false);
				Clause cls;
				cls.Add(neg_p_h);
				cls.Add(neg_p2_h);
				formula.Add(cls);
			}
		}
	}
}

int main(int argc, const char* argv[])
{
	if (2 != argc
		&& 3 != argc)
	{
		std::cout << "pigon_hold_10 <number of holes> [<number of pigeons>]" << std::endl;
		return -1;
	}
	else
	{
		//cout << argv[0] << " " << argv[1] << endl;
		int n_hole = atoi(argv[1]);
		int n_pigeon = (3 == argc)
			? atoi(argv[2])
			: n_hole + 1;
		Formula formula(n_hole * n_pigeon);
		std::cout << "c put " << n_pigeon << " pigeons into " << n_hole << " holes!" << std::endl;
		EveryPigeonInAhole(n_pigeon, n_hole, formula);
		NoHolesCanHoldMoreThanOnePigeon(n_pigeon, n_hole, formula);
		formula.Dump(std::cout);
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
