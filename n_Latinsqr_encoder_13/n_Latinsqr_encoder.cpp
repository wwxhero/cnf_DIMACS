// n_Latinsqr_encoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "logicBase.h"
void PermutationRow(int n_squares, Formula& fla)
{
	//for every row is a permuatation of the numbers from N
}

void PermutationCol(int n_squares, Formula& fla)
{
	//for every col is a permuatation of the numbers from N
}

void XstarXeqX(int n_squares, Formula& fla)
{
	//x * x = x for x in {0, ..., n-1}
}

void Steins3rdLaw(int n_squares, Formula& fla)
{
	//(x*y) * (y*x) = y
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
    	PermutationRow(n_latin, fla);
    	PermutationCol(n_latin, fla);
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
