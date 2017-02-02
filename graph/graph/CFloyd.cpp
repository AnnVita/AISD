#include "stdafx.h"
#include "Floyd.h"

void Floyd::Initialise()
{
	m_matrixPath.resize(m_matrix.size());
	for (size_t i = 0; i < m_matrix.size(); ++i)
		m_matrixPath[i].resize(m_matrix.size());
	for (size_t i = 0; i < m_matrixPath.size(); ++i)
	{
		for (size_t j = 0; j < m_matrixPath.size(); ++j)
		{
			if (m_matrix[i][j] == 10000)
				m_matrixPath[i][j] = 10000;
			else
				m_matrixPath[i][j] = j;
		}
	}
	Copy();
}

void Floyd::FindPathMatrix()
{
	for (size_t k = 0; k < m_matrix.size(); ++k)
	{
		for (size_t i = 0; i < m_matrix.size(); ++i)
		{
			for (size_t j = 0; j < m_matrix.size(); ++j)
			{
				int b = m_matrixShortestPath[i][k] + m_matrixShortestPath[k][j];
				if (b < m_matrixShortestPath[i][j])
				{
					m_matrixShortestPath[i][j] = b;
					m_matrixPath[i][j] = k;
				}
			}
		}
	}
}

void Floyd::FindPath(size_t first, size_t second)
{
	if (first >= m_matrixPath.size() || second >= m_matrixPath.size())
		throw std::invalid_argument("One of nodes for searching is more than matrix size");
	if (m_matrixShortestPath[first][second] < 10000)
	{
		Stack Goals;
		Path.push(first);
		Goals.push(second);
		while (!Goals.empty())
		{
			int u = Path.top();
			int v = Goals.top();
			int s = m_matrixPath[u][v];
			if (v == s)
			{
				Path.push(v);
				Goals.pop();
			}
			else
				Goals.push(s);
		}
	}
}

void Floyd::PrintWeightMatrix(std::ostream & os) const
{
	PrintMatrix(m_matrix, os);
}

void Floyd::PrintShortestPathPMatrix(std::ostream & os) const
{
	PrintMatrix(m_matrixShortestPath, os);
}

void Floyd::PrintPathMatrix(std::ostream & os) const
{
	PrintMatrix(m_matrixPath, os);
}

void Floyd::PrintSt(std::ostream & os, size_t first, size_t second)
{
	std::string temp;
	while (!Path.empty())
	{
		temp += std::to_string(Path.top() + 1);
		temp += ' ';
		Path.pop();
	}
	if (m_matrixShortestPath[first][second] < 10000)
	{
		std::reverse(temp.begin(), temp.end());
		os << temp << std::endl; 
		os << "Path length = " << m_matrixShortestPath[first][second] << std::endl;
	}
	else
	{
		os << "No path" << std::endl;
	}
}

void Floyd::PrintMatrix(const Matrix & vec, std::ostream & os) const
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = 0; j < vec.size(); ++j)
		{
			if (vec[i][j] < 10000)
			{
				os << std::setw(4) << vec[i][j] << ' ';
			}
			else
			{
				os << std::setw(4) << "*";
			}
		}
		os << std::endl;
	}
}

void Floyd::Copy()
{
	m_matrixShortestPath.resize(m_matrix.size());
	for (size_t i = 0; i < m_matrix.size(); ++i)
		m_matrixShortestPath[i].resize(m_matrix.size());
	for (size_t i = 0; i < m_matrix.size(); ++i)
		std::copy(m_matrix[i].begin(), m_matrix[i].end(), m_matrixShortestPath[i].begin());
}