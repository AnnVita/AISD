#pragma once
#include "stdafx.h"

class CExpressionParsingError : public std::invalid_argument
{
public:
	CExpressionParsingError(const std::string & message)
		: std::invalid_argument(message)
	{ };
private:
	std::string m_base;
};