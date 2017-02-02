#include "stdafx.h"
#include "Matrix.h"

void CMatrixAdjacent::SetSize(const size_t n)
{
	m_matrix.resize(n);
	for (size_t i = 0; i < n; ++i)
		m_matrix[i].resize(n);
}

void CMatrixAdjacent::Fill(std::istream & istrm)
{
	std::string answer;
	for (size_t i = 0; i < m_matrix.size(); ++i)
	{
		for (size_t j = 0; j < m_matrix.size(); ++j)
		{
			if (i == j)
				m_matrix[i][j] = 0;
			/*else if (i > j)
			{
				m_matrix[i][j] = m_matrix[j][i];
			}*/
			else
			{
				std::cout << "Enter weight of V" << i+1 << ",V" << j+1 << " edge" << std::endl << "* for not connect them" << std::endl;
				istrm >> answer;
				if (answer == "*")
					m_matrix[i][j] = 10000;
				else
					m_matrix[i][j] = std::stoi(answer);
			}
		}
	}
}
