#pragma once
#include "stdafx.h"

enum NodeType
{
	AND, OR, LEAF
};

class CAndOrTree
{
public:
	struct Node
	{
		NodeType type;
		std::string name;
		Node * left, *right;
	};

	CAndOrTree(std::istream & input, std::ostream & output);

	void StartInit();
	void StartPrint();
	void StartPrintConfigurations();

private:
	NodeType GetType(std::string source);
	void InitTree(Node ** node);
	void PrintTree(Node ** node, size_t lvl);
	void FillConfigurations(Node ** node);
	std::string ConfigurateLogicIdent(size_t lvl);

	std::istream & m_input;
	std::ostream & m_output;
	Node * m_root;
	size_t m_lvl = 0;
	std::deque<std::string> m_configuration;
	std::stack<std::string> m_ORStack;
};
