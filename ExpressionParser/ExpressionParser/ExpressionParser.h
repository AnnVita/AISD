#pragma once
#include "stdafx.h"

static const char UNARY_PLUS_CH = '&';
static const char UNARY_MINUS_CH = '?';

static const std::string UNARY_PLUS_ST = std::to_string(UNARY_PLUS_CH);
static const std::string UNARY_MINUS_ST = std::to_string(UNARY_MINUS_CH);

class CExpressionParser
{
public:
	struct Node
	{
		std::string value;
		Node * left;
		Node * right;
	};

	CExpressionParser(const std::string & expression);
	~CExpressionParser();
	void BuildTree();
	void StartPrintTree() const;
	void PrintPostfix();

private:
	void ConvertToPostfix();
	void CheckBrackets();
	static void PrintTree(Node * root, size_t lvl);
	static std::string ConfigurateLogicIdent(size_t lvl);
	void RemakeUnaryOperations();
	bool IsOperator(const std::string & mathOperator);
	size_t Priority(const std::string & op);

	void DeleteTree(Node * node);

	std::string m_expression;
	Node * m_root = nullptr;
	std::set<std::string> m_operations;
	std::deque<std::string> m_postfixExpression;
};