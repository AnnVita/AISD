#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

static const int NECESSARY_NUM_OF_ARGUMENTS = 3;
static const char OLD_COMMENT_OPENING_BRACKET = '(';
static const char OLD_COMMENT_CLOSING_BRACKET = ')';
static const char OLD_COMMENT_NEXT_SYMBOL = '*';
static const char NORMAL_COMMENT_OPENING_BRACKET = '{';
static const char NORMAL_COMMENT_CLOSING_BRACKET = '}';

struct Stack
{
	std::string key;
	Stack * next;
};

void push(Stack ** top, const std::string & newRecord);
void pop(Stack ** top);
bool GetTopValue(Stack ** top, std::string & topValue);
void CleanStack(Stack ** top);
bool IsStackEmpty(Stack ** top);

void CheckComments(const std::string & haystack, Stack ** top, bool & wasError);
bool RightNestedCommentsClosing(Stack ** top, std::string bracket);
std::string Replace(const std::string & haystack, const std::string needle, const std::string replace);
void RewriteFile(std::ifstream & input, std::ofstream & output, Stack ** top);
void IgnoreInApostropheSymbols(const std::string & haystack, size_t & counter);

void ShowStackValues(Stack ** top);

int main(int argc, char * argv[])
{
	if (argc != NECESSARY_NUM_OF_ARGUMENTS)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: commentControl.exe <input file>";
		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cout << "Unable to open input file" << std::endl;
		return EXIT_FAILURE;
	}
	std::string programLine;
	Stack * top = nullptr;
	bool wasError = false;
	size_t lineCounter;


	for (lineCounter = 1; getline(input, programLine) && !wasError; ++lineCounter)
	{
		CheckComments(programLine, &top, wasError);
	}
	wasError = (!wasError) ? !IsStackEmpty(&top) : true;

	input.close();
	input.clear();
	input.open(argv[1]);

	CleanStack(&top);

	if (!wasError)
	{
		std::ofstream output(argv[2]);
		RewriteFile(input, output, &top);
	}
	else
	{
		std::cout << "Error was founded on line:" << lineCounter - 1 << std::endl;
	}

	return EXIT_SUCCESS;
}

void ShowStackValues(Stack ** top)
{
	Stack * temp = *top;
	while (temp)
	{
		std::cout << temp->key << std::endl;
		temp = temp->next;
	}
}

void CleanStack(Stack ** top)
{
	while (*top != nullptr)
	{
		pop(top);
	}
}

void push(Stack ** top, const std::string & newBracket)
{
	Stack * temp = new Stack;
	temp->key = newBracket;
	temp->next = *top;
	*top = temp;
}

void pop(Stack ** top)
{
	Stack * temp = *top;
	*top = (*top)->next;
	delete temp;
}

bool GetTopValue(Stack ** top, std::string & topValue)
{
	if (!IsStackEmpty(top))
	{
		topValue = ((*top)->key);
		return true;
	}
	else
	{
		return false;
	}
}

bool IsStackEmpty(Stack ** top)
{
	return (*top == nullptr);
}

void CheckComments(const std::string & haystack, Stack ** top, bool & wasError)
{
	std::string newBracket;
	for (size_t i = 0; (i < haystack.length()) && !wasError; ++i)
	{
		IgnoreInApostropheSymbols(haystack, i);
		switch (haystack[i])
		{
		case '}':
			newBracket = NORMAL_COMMENT_CLOSING_BRACKET;
			wasError = !RightNestedCommentsClosing(top, newBracket);
			if (!wasError)
				pop(top);
			break;
		case '{':
			newBracket = NORMAL_COMMENT_OPENING_BRACKET;
			push(top, newBracket);
			break;
		case '(':
			if (haystack[i + 1] == '*')
			{
				newBracket = "(*";
				push(top, newBracket);
			}
			break;
		case ')':
			if (haystack[i - 1] == '*')
			{
				newBracket = "*)";
				wasError = !RightNestedCommentsClosing(top, newBracket);
				if (!wasError)
					pop(top);
			}
			break;
		default:
			break;
		}
	}
}

bool RightNestedCommentsClosing(Stack ** top, std::string bracket)
{
	Stack * temp = *top;
	if (temp != nullptr)
	{
		std::string lastBracket = temp->key;
		std::string oppositeBracket = (bracket == "}") ? "{" : "(*";
		return (lastBracket == oppositeBracket);
	}
	return false;
}

void RewriteFile(std::ifstream & input, std::ofstream & output, Stack ** top)
{
	std::string programLine;
	std::string newLine = "";
	bool insideComment = false;
	size_t prevPos = 0;
	while (getline(input, programLine))
	{
		programLine = Replace(programLine, "(*", "{");
		programLine = Replace(programLine, "*)", "}");
		newLine = "";
		prevPos = 0;
		for (size_t i = 0; i < programLine.length(); ++i)
		{
			IgnoreInApostropheSymbols(programLine, i);
			if (programLine[i] == NORMAL_COMMENT_OPENING_BRACKET)
			{
				newLine += programLine.substr(prevPos, i - prevPos);
				prevPos = i + 1;
				if (IsStackEmpty(top))
				{
					newLine += "{";
				}
				push(top, "{");
			}
			else if (programLine[i] == NORMAL_COMMENT_CLOSING_BRACKET)
			{
				newLine += programLine.substr(prevPos, i - prevPos);
				prevPos = i + 1;
				pop(top);
				if (IsStackEmpty(top))
				{
					newLine += "}";
				}
			}
		}
		newLine += programLine.substr(prevPos);
		output << newLine << std::endl;
	}
}

std::string Replace(const std::string & haystack, const std::string needle, const std::string replace)
{
	int prevPos = 0, currFoundedPos = 0;
	std::string result = "";

	while ((currFoundedPos = int(haystack.find(needle, prevPos))) != std::string::npos)
	{
		result += haystack.substr(prevPos, currFoundedPos - prevPos);
		result += replace;
		prevPos = currFoundedPos + int(needle.length());
	}
	return result += haystack.substr(prevPos);
}

void IgnoreInApostropheSymbols(const std::string & haystack, size_t & counter)
{
	if (haystack[counter] == '\'')
	{
		for (++counter; (haystack[counter] != '\'') && (counter < haystack.length()); ++counter);
	}
}