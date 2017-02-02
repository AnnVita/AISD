#pragma once
#include "stdafx.h"

class CMatrixAdjacent
{
public:
	CMatrixAdjacent() {};
	virtual ~CMatrixAdjacent() {};
	void SetSize(const size_t n);
	void Fill(std::istream & istrm);

protected:
	Matrix m_matrix;
};