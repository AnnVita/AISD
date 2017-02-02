//Имеется  некоторое  алгебраическое выражение.Операнды
//заданы идентификаторами, операции выполняются по приоритетам,
//допускается использование круглых скобок.Требуется построить
//и выдать в  наглядном  виде  бинарное  дерево, представляющее
//данное выражение(12).

#include "stdafx.h"
#include "ExpressionParser.h"
#include "CExpressionParsingError.h"

int main()
{
	std::string expressionStr;
	while (std::getline(std::cin, expressionStr))
	{
		try
		{
			CExpressionParser expression(expressionStr);
			expression.PrintPostfix();
			expression.BuildTree();
			expression.StartPrintTree();
		}
		catch (CExpressionParsingError & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}