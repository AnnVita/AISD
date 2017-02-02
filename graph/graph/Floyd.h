#pragma once
#include "stdafx.h"
#include "Matrix.h"

static const int MAX_c = 100;

class Floyd : public CMatrixAdjacent
{
public:
	Floyd() : CMatrixAdjacent() {};

	~Floyd() {};

	void Initialise();
	void FindPathMatrix();
	void FindPath(size_t first, size_t second);
	void PrintWeightMatrix(std::ostream & os) const;
	void PrintShortestPathPMatrix(std::ostream & os) const;
	void PrintPathMatrix(std::ostream & os) const;
	void PrintSt(std::ostream & os, size_t first, size_t second);

private:
	Matrix m_matrixPath;
	Matrix m_matrixShortestPath;
	Stack Path;

	void PrintMatrix(const Matrix & matrix, std::ostream & os) const;
	void Copy();
};

