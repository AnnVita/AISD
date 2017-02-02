#pragma once
#include "stdafx.h"

class CBadBracketGenerationInfo : public std::invalid_argument
{
public:
	CBadBracketGenerationInfo(const std::string & message)
		: std::invalid_argument(message)
	{ };
private:
	std::string m_base;
};