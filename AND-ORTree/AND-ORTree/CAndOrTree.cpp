#include "stdafx.h"
#include "CAndOrTree.h"

CAndOrTree::CAndOrTree(std::istream & input, std::ostream & output)
	: m_input(input)
	, m_output(output)
{
	m_root = new Node;
	m_configuration.push_front("");
};

void CAndOrTree::InitTree(Node ** node)
{
	if (*node != nullptr)
	{
		m_input >> (*node)->name;
		std::string type;
		m_input >> type;
		(*node)->type = GetType(type);
		if ((*node)->type == NodeType::LEAF)
		{
			(*node)->left = nullptr;
		}
		else
		{
			Node * newNode = new Node();
			(*node)->left = newNode;
		}
		InitTree(&(*node)->left);
		if (*node == m_root)
		{
			(*node)->right = nullptr;
			return;
		}
		std::string rightNeighborFlag;
		m_input >> rightNeighborFlag;
		if (rightNeighborFlag == "1")
		{
			Node * newNode = new Node();
			(*node)->right = newNode;

		}
		else
		{
			(*node)->right = nullptr;
		}
		InitTree(&(*node)->right);
	}
}

NodeType CAndOrTree::GetType(std::string source)
{
	if (source == "and")
	{
		return NodeType::AND;
	}
	else if (source == "or")
	{
		return NodeType::OR;
	}
	else
	{
		return NodeType::LEAF;
	}
}

void CAndOrTree::PrintTree(Node ** node, size_t lvl)
{
	if (*node != nullptr)
	{
		PrintTree(&(*node)->right, lvl);
		if ((*node) != m_root)
			lvl++;
		m_output << ConfigurateLogicIdent(lvl);
		if (lvl != 0)
			m_output << static_cast<char>(192) << "-";
		m_output << (*node)->name << " " << (*node)->type << std::endl;
		PrintTree(&(*node)->left, lvl);
	}
}

void CAndOrTree::FillConfigurations(Node ** node)
{
	if (*node != nullptr)
	{
		std::string tempString;
		FillConfigurations(&(*node)->right);
		
		if ((*node)->type == NodeType::OR)
		{
			Node * tempNode = (*node)->left;
			while (tempNode != nullptr)
			{
				if (tempNode->type == NodeType::LEAF)
				{
					m_ORStack.push(tempString + tempNode->name);
				}
				else
				{
					FillConfigurations(&tempNode);
				}
				tempNode = tempNode->right;
			}
		}
		else
		{
			tempString += (*node)->name;
		}
		FillConfigurations(&(*node)->left);
		if (!tempString.empty())
			m_configuration.push_front(tempString);
	}
}

void CAndOrTree::StartPrintConfigurations()
{
	FillConfigurations(&m_root);
	m_output << m_configuration.size() << std::endl;
	for (size_t i = 0; i < m_configuration.size(); ++i)
	{
		m_output << m_configuration[i] << std::endl;
	}
}

std::string CAndOrTree::ConfigurateLogicIdent(size_t lvl)
{
	std::string result = "";
	if (lvl != 0)
	{
		for (; lvl > 0; --lvl)
		{
			result += " ";
		}
	}
	return result;
}

void CAndOrTree::StartInit()
{
	InitTree(&m_root);
}

void CAndOrTree::StartPrint()
{
	PrintTree(&m_root, m_lvl);
}
