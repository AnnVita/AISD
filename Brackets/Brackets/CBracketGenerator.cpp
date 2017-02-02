#include "stdafx.h"
#include "BracketsGenerator.h"

CBracketGenerator::CBracketGenerator(unsigned length)
{
	if (length % 2 != 0 || length > 16)
		throw CBadBracketGenerationInfo("Invalid length!");
	m_length = length;
	m_generationEnded = false;
}

void CBracketGenerator::GenerateCombinations()
{
	std::string nextCombination = std::string(m_length / 2, '(') + std::string(m_length / 2, ')');
	while (!m_generationEnded)
	{
		m_combinations.push_back(nextCombination);
		nextCombination = FindNextBracketCombinations(m_combinations.back());
	}
}

std::string CBracketGenerator::FindNextBracketCombinations(const std::string & bracketString)
{
	int n = static_cast<int>(bracketString.length());
	for (int i = n - 1, depth = 0; i >= 0; --i)
	{
		if (bracketString[i] == '(')
			--depth;
		else
			++depth;
		if (bracketString[i] == '(' && depth > 0)
		{
			--depth;
			int open = (n - i - 1 - depth) / 2;
			int close = n - i - 1 - open;
			return bracketString.substr(0, i) + ')' + std::string(open, '(') + std::string(close, ')');
		}
	}
	m_generationEnded = true;
	return "";
}

void CBracketGenerator::PrintCombinations(std::ostream & os)
{
	for (size_t i = 0; i < m_combinations.size(); ++i)
	{
		os << m_combinations[i] << std::endl;
	}
}