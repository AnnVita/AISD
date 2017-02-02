#include "stdafx.h"
#include "ExpressionParser.h"
#include "CExpressionParsingError.h"

CExpressionParser::CExpressionParser(const std::string & expression)
	: m_expression(expression)
{
	CheckBrackets();
	m_root = nullptr;
	m_operations = { "+", "-", "*", "/", "^", "(", ")", "&", "?"};
	ConvertToPostfix();
}

void CExpressionParser::CheckBrackets()
{
	std::stack<char> stack;
	std::string newString;
	for (size_t i = 0; i < m_expression.size(); ++i)
	{
		if (m_expression[i] == '(')
		{
			stack.push('(');
		}
		else if (m_expression[i] == ')')
		{
			if (!stack.empty())
				stack.pop();
			else
				throw CExpressionParsingError("Wrong nesting!");
		}

	}
	if (!stack.empty())
	{
		throw CExpressionParsingError("Wrong nesting!");
	}
}

bool CExpressionParser::IsOperator(const std::string & mathOperator)
{
	return m_operations.find(mathOperator) != m_operations.end();
}

void CExpressionParser::RemakeUnaryOperations()
{
	for (size_t i = 0; i < m_expression.length(); i++)
	{
		if (m_expression[0] == '-' || m_expression[0] == '+')
		{
			(m_expression[0] == '-') ? m_expression[0] = UNARY_MINUS_CH : m_expression[0] = UNARY_PLUS_CH;
		}
		else if (i != 0 && m_expression[i - 1] == '(' && (m_expression[i] == '-' || m_expression[i] == '+'))
		{
			(m_expression[i] == '-') ? m_expression[i] = UNARY_MINUS_CH : m_expression[i] = UNARY_PLUS_CH;
		}
	}
}

void CExpressionParser::ConvertToPostfix()
{
	std::string element;
	std::stack<std::string> stack;
	bool isValidExpresion = true;
	std::string operandName;
	int openFrame = 0;
	RemakeUnaryOperations();

	for (size_t i = 0; i < m_expression.length(); i++)
	{
		element = m_expression[i];
		if (!IsOperator(element))
		{
			operandName += element;
			if (i != m_expression.length() - 1)
			{
				i++;
				element = m_expression[i];
				while (!IsOperator(element))
				{
					operandName += element;
					i++;
					element = m_expression[i];
				}
			}
			m_postfixExpression.push_back(operandName);
			operandName = "";
		}
		if (IsOperator(element))
		{
			if (stack.size() == 0)
			{
				stack.push(element);
			}
			else if (m_expression[i] == ')' || m_expression[i] == '(')
			{
				if (m_expression[i] == '(')
				{
					openFrame++;
					stack.push(element);
				}
				else  if (m_expression[i] == ')' && openFrame >= 0)
				{
					openFrame--;
					while (stack.top() != "(" && stack.size() != 0)
					{
						m_postfixExpression.push_back(stack.top());
						stack.pop();
					}
					if (!stack.empty() && stack.top() == "(")
					{
						stack.pop();
					}
				}
			}
			else
			{
				element = m_expression[i];
				if (Priority(element) < Priority(stack.top()))
				{
					while (stack.size() > 0 && (Priority(element) <= Priority(stack.top()) && stack.top() != "("))
					{
						m_postfixExpression.push_back(stack.top());
						stack.pop();
					}

					stack.push(element);
				}
				else
				{
					stack.push(element);
				}
			}
		}
	}
	while (stack.size() != 0)
	{
		m_postfixExpression.push_back(stack.top());
		stack.pop();
	}
}

void CExpressionParser::PrintPostfix()
{
	for (size_t i = 0; i < m_postfixExpression.size(); ++i)
	{
		std::cout << m_postfixExpression[i] << " | ";
	}
	std::cout << std::endl;
}

void CExpressionParser::BuildTree()
{
	std::stack <Node *> treeStack;
	Node * newNode;
	for (int i = 0; i < m_postfixExpression.size(); i++)
	{
		if (!IsOperator(m_postfixExpression[i]))
		{
			newNode = new Node;
			newNode->value = m_postfixExpression[i];
			newNode->left = nullptr;
			newNode->right = nullptr;
			treeStack.push(newNode);
		}
		else
		{
			newNode = new Node;
			newNode->value = m_postfixExpression[i];
			newNode->left = treeStack.top();
			treeStack.pop();
			if (!treeStack.empty() && !(m_postfixExpression[i] == "?" || m_postfixExpression[i] == "&"))
			{
				if ((treeStack.top())->value == "?" || (treeStack.top())->value == "&")
				{
					(treeStack.top()->value == "?" ? treeStack.top()->value = "-" : treeStack.top()->value = "+");
				}
				newNode->right = treeStack.top();
				if (!treeStack.empty())
				{
						treeStack.pop();
				}
			}
			else
			{
				newNode->right = nullptr;
			}
			if (newNode->value == "^")
			{
				std::swap(newNode->left, newNode->right);
			}
			treeStack.push(newNode);
		}
	}
	if (!treeStack.empty())
	{
		m_root = treeStack.top();
	}
	else
	{
		throw CExpressionParsingError("Bad string!");
	}
}

void CExpressionParser::StartPrintTree() const
{
	size_t lvl = 0;
	PrintTree(m_root, lvl);
}

void CExpressionParser::PrintTree(Node * root, size_t lvl)
{
	if (root != nullptr)
	{
		if (root->value == "?" || root->value == "&")
		{
			(root->value == "?" ? root->value = "-" : root->value = "+");
		}
		std::cout << ConfigurateLogicIdent(lvl) + root->value << std::endl;
		++lvl;
		PrintTree(root->left, lvl);
		PrintTree(root->right, lvl);
	}
}

std::string CExpressionParser::ConfigurateLogicIdent(size_t lvl)
{
	std::string result;
	if (lvl != 0)
	{
		for (; lvl > 0; --lvl)
		{
			result += " ";
		}
	}
	return result;
}

CExpressionParser::~CExpressionParser()
{
	DeleteTree(m_root);
}

void CExpressionParser::DeleteTree(Node * node)
{
	if (node != nullptr)
	{
		DeleteTree(node->left);
		DeleteTree(node->right);
		free(node);
	}
}

size_t CExpressionParser::Priority(const std::string & op)
{
	if (op == "(" || op == ")")
		return 0;
	if (op == "+" || op == "-")
		return 1;
	if (op == "*" || op == "/")
		return 2;
	if (op == "^")
		return 3;
	if (op == "&" || op == "?")
		return 4;
	return 0;
}