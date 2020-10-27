// pigeon_hold_10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <sstream>
namespace DIMACS
{
	typedef std::string Literal;
	typedef std::list<Literal> Clause;
	typedef std::list<Clause> Formula;

	inline Literal PigeonInHole(int i_pigeon, int n_pigeon, int i_hole, int n_hole, bool val)
	{
#ifdef _DEBUG
		std::ostringstream oss;
		if (val)
			oss << i_pigeon << "_" << i_hole;
		else
			oss << i_pigeon << "_" << i_hole << "'";
		return std::move(oss.str());
#else
		std::ostringstream oss;
		int lit = i_pigeon * n_hole + i_hole + 1;
		if (!val)
			lit = -lit;
		oss << lit;
		return std::move(oss.str());
#endif
	}


	inline void EveryPigeonInAhole(int n_pigeon, int n_hole, Formula& formula)
	{
		for (int i_pigeon = 0; i_pigeon < n_pigeon; i_pigeon ++)
		{
			Clause p_inhole;
			for (int i_hole = 0; i_hole < n_hole; i_hole ++)
			{
				p_inhole.push_back(PigeonInHole(i_pigeon, n_pigeon, i_hole, n_hole, true));
			}
			formula.push_back(p_inhole);
		}
	}

	inline void NoHolesCanHoldMoreThanOnePigeon(int n_pigeon, int n_hole, Formula& formula)
	{
		for (int i_hole = 0; i_hole < n_hole; i_hole ++)
		{
			for (int i_pigeon = 0; i_pigeon < n_pigeon - 1; i_pigeon ++)
			{
				Literal neg_p_h = PigeonInHole(i_pigeon, n_pigeon, i_hole, n_hole, false);
				for (int i_pigeon2 = i_pigeon + 1; i_pigeon2 < n_pigeon; i_pigeon2 ++)
				{
					Literal neg_p2_h = PigeonInHole(i_pigeon2, n_pigeon, i_hole, n_hole, false);
					Clause cls;
					cls.push_back(neg_p_h);
					cls.push_back(neg_p2_h);
					formula.push_back(cls);
				}
			}
		}
	}

	inline std::string ClauseStr(const Clause& cls)
	{
#ifdef _DEBUG
		auto it_l = cls.begin();
		std::ostringstream oss;
		oss << *it_l ++;
		for (
			; it_l != cls.end()
			; it_l ++)
		{
			oss << "|" << *it_l;
		}
		return std::move(oss.str());
#else
		auto it_l = cls.begin();
		std::ostringstream oss;
		oss << *it_l ++;
		for (
			; it_l != cls.end()
			; it_l ++)
		{
			oss << " " << *it_l;
		}
		oss << " 0";
		return std::move(oss.str());
#endif
	}

	inline void Dump(std::ostream& out, const Formula& formula, int n_pigeon, int n_hole)
	{
#ifdef _DEBUG
		out << "{" << std::endl;
		auto it_c = formula.begin();
		out << "\t" << ClauseStr(*it_c ++);
		for (
			; it_c != formula.end()
			; it_c ++)
		{
			out << std::endl << "\t, " << ClauseStr(*it_c);
		}
		out << std::endl << "}" << std::endl;
#else
		out << "c put " << n_pigeon << " pigeons into " << n_hole <<" holes!" <<std::endl;
		out << "p cnf " << n_pigeon * n_hole << " " << formula.size() << std::endl;
		auto it_c = formula.begin();
		out << ClauseStr(*it_c ++);
		for (
			; it_c != formula.end()
			; it_c ++)
		{
			out << std::endl << ClauseStr(*it_c);
		}
#endif
	}
};




int main(int argc, const char* argv[])
{
    if (2 != argc
    	&& 3 != argc)
    {
    	std::cout << "pigon_hold_10 <number of holes> [<number of pigeons>]" <<std::endl;
    	return -1;
    }
    else
    {
    	//cout << argv[0] << " " << argv[1] << endl;
    	int n_hole = atoi(argv[1]);
    	int n_pigeon = (3 == argc)
    					? atoi(argv[2])
    					: n_hole + 1;
    	DIMACS::Formula formula;
    	DIMACS::EveryPigeonInAhole(n_pigeon, n_hole, formula);
    	DIMACS::NoHolesCanHoldMoreThanOnePigeon(n_pigeon, n_hole, formula);
    	DIMACS::Dump(std::cout, formula, n_pigeon, n_hole);
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
