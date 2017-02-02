//Реализовать алгоритм поиска кратчайших путей  Флойда  и
//проиллюстрировать по шагам этапы его выполнения(9).

#include "stdafx.h"
#include "Matrix.h"
#include "Floyd.h"

int main(int argc, char * argv[])
{
	try
	{
	int n;
		std::cout << "Enter number of nodes: ";
		std::cin >> n;
		Floyd Graph;
		Graph.SetSize(n);
		if (argc >= 2)
		{
			std::ifstream input(argv[1]);
			Graph.Fill(input);
		}
		else
		{
			Graph.Fill(std::cin);
		}
		Graph.Initialise();
		Graph.FindPathMatrix();
		size_t first, second;
		
		Graph.PrintPathMatrix(std::cout);
		std::cout << "______________________________" << std::endl;
		Graph.PrintShortestPathPMatrix(std::cout);

		char ch = 'y';
		do
		{
			if (!(ch == 'y' || ch == 'Y'))
				break;
			std::cout << "Enter first and second nodes for search path between them\n";
			std::cin >> first >> second;
			Graph.FindPath(first - 1, second - 1);
			std::cout << "Shortest path between " << first << " and " << second << " nodes is\n";
			Graph.PrintSt(std::cout, first - 1, second - 1);
			std::cout << "Contunue?(y/Y)" << std::endl;
		} while (std::cin >> ch);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << '\n';
		return 1;
	}
	return 0;
}
