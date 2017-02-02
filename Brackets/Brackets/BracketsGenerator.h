#pragma once
#include "stdafx.h"
#include "CBadBracketGenerationInfo.h"

class CBracketGenerator
{
public:
	CBracketGenerator(unsigned length);

	virtual void GenerateCombinations();
	void PrintCombinations(std::ostream & os);

protected:
	virtual std::string FindNextBracketCombinations(const std::string & bracketString);

	unsigned m_length;
	std::string m_firstCombination;
	std::deque<std::string> m_combinations;
	bool m_generationEnded;
};