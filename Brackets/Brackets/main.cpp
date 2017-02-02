// Brackets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BracketsGenerator.h"

using namespace std;

int main()
{
	unsigned length;
	cin >> length;
	try
	{
		CBracketGenerator bracketGenerator(length);
		bracketGenerator.GenerateCombinations();
		bracketGenerator.PrintCombinations(cout);
		return 0;
	}
	catch (CBadBracketGenerationInfo & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}

