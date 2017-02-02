#include "stdafx.h"
#include "CAndOrTree.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: AND-ORTree.exe <input>\n";
		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1]);

	CAndOrTree tree(input, std::cout);
	tree.StartInit();
	//tree.StartPrint();
	tree.StartPrintConfigurations();
    return 0;
}

