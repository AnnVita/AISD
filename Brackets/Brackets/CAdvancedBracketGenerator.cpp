#include "stdafx.h"
#include "AdvancedBracketGenerator.h"

CAdvancedBracketGenerator::CAdvancedBracketGenerator(unsigned length)
	: CBracketGenerator(length)
{
}

void CAdvancedBracketGenerator::GenerateBasicBracketsString()
{
	std::string tempString;
	for (size_t i = 0; i < tempString.length(); i++)
	{
		tempString = std::string(m_length - i, '(') + std::string(i, '[');
		GenerateBasicCombinations(tempString);
	}
}

void CAdvancedBracketGenerator::GenerateCombinations()
{
	for (size_t i = 0; i < m_bracketsCombinations.size(); ++i)
	{
		std::string nextCombination = m_bracketsCombinations[i];
		while (!m_generationEnded)
		{
			m_combinations.push_back(nextCombination);
			nextCombination = FindNextBracketCombinations(m_combinations.back());
		}
	}
}

std::string CAdvancedBracketGenerator::GenerateBracketString(std::vector<bool> bracketType)
{
	std::string result;
	for (size_t i = 0; i < bracketType.size(); ++i)
	{
		std::string tempString = (!bracketType[i]) ? "(" : "[";
		result += tempString;
	}
	std::string closeBrackets;
	for (size_t i = 0; i < result.size(); ++i)
	{
		std::string tempString = (result[i] == '(') ? ")" : "]";
		closeBrackets += tempString;
	}
	result += closeBrackets;
	return result;
}

std::string CAdvancedBracketGenerator::FindNextBracketCombinations(const std::string & bracketString)
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