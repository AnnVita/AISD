#pragma once
#include "BracketsGenerator.h"

class CAdvancedBracketGenerator : public CBracketGenerator
{
public:
	CAdvancedBracketGenerator(unsigned length);
	void GenerateCombinations() override;
private:
	virtual std::string FindNextBracketCombinations(const std::string & bracketString) override;
	void GenerateBasicBracketsString();
	void GenerateBasicCombinations(std::string base);
	std::string GenerateBracketString(std::vector<bool> bracketType);
	std::vector<std::string> m_bracketsCombinations;
};