#include <iostream>
#include <fstream>
#include <string>

static const int NECESSARY_NUM_OF_ARGUMENTS = 2;
static const char OLD_COMMENT_OPENING_BRACKET = '(';
static const char OLD_COMMENT_CLOSING_BRACKET = ')';
static const char OLD_COMMENT_NEXT_SYMBOL = '*';
static const char NORMAL_COMMENT_OPENING_BRACKET = '{';
static const char NORMAL_COMMENT_CLOSING_BRACKET = '}';

struct KeyType
{
	std::string commentBracket;
	size_t lineNum;
};

struct Stack
{
	KeyType key;
	Stack * next;
};

void push(Stack ** top, const KeyType & newRecord);
void pop(Stack ** top);
bool GetTopValue(Stack ** top, KeyType & topValue);
void HandleProcessingComments(const std::string & haystack, Stack ** top, size_t lineNum);

void ShowStackValues(Stack * top);

int main(int argc, char * argv[])
{
	if (argc != NECESSARY_NUM_OF_ARGUMENTS)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: commentControl.exe <input file>";
		return EXIT_FAILURE;
	}

	std::string fileName = argv[1];
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		std::cout << "Unable to open input file" << std::endl;
		return EXIT_FAILURE;
	}

	std::string programLine;
	Stack * top = nullptr;

	for (size_t lineCounter = 0; getline(input, programLine); ++lineCounter)
	{
		HandleProcessingComments(programLine, &top, lineCounter);
	}

	ShowStackValues(top);
	/*if (!output.flush())
	{
	std::cout << "Failed to save data on disk\n";
	return EXIT_FAILURE;
	}*/

	return EXIT_SUCCESS;
}

void ShowStackValues(Stack * top)
{
	Stack * temp = top;
	while (temp)
	{
		std::cout << temp -> key.commentBracket << std::endl;
		temp = temp -> next;
	}
}

void push(Stack ** top, const KeyType & newRecord)
{
	Stack * temp = new Stack;
	temp -> key = newRecord;
	temp -> next = *top;
	*top = temp;
}

void pop(Stack ** top)
{
	Stack * temp = *top;
	*top = (*top) -> next;
	delete temp;
}

bool GetTopValue(Stack ** top, KeyType & topValue)
{
	if (*top != nullptr)
	{
		topValue = ((*top)->key);
		return true;
	}
	else
	{
		return false;
	}
}

void HandleProcessingComments(const std::string & haystack, Stack ** top, size_t lineNum)
{
	KeyType newRecord;
	for (size_t i = 0; i < haystack.length(); ++i)
	{
		switch (haystack[i])
		{
		case NORMAL_COMMENT_CLOSING_BRACKET:
			newRecord.commentBracket = NORMAL_COMMENT_CLOSING_BRACKET;
			newRecord.lineNum = lineNum;
			push(top, newRecord);
			break;
		case NORMAL_COMMENT_OPENING_BRACKET:
			newRecord.commentBracket = NORMAL_COMMENT_OPENING_BRACKET;
			newRecord.lineNum = lineNum;
			push(top, newRecord);
			break;
		case OLD_COMMENT_OPENING_BRACKET:
			if (haystack[i + 1] == OLD_COMMENT_NEXT_SYMBOL)
			{
				newRecord.commentBracket = "" + OLD_COMMENT_OPENING_BRACKET + OLD_COMMENT_NEXT_SYMBOL;
				newRecord.lineNum = lineNum;
				push(top, newRecord);
			}
			break;
		case OLD_COMMENT_CLOSING_BRACKET:
			if (haystack[i - 1] == OLD_COMMENT_NEXT_SYMBOL)
			{
				newRecord.commentBracket ="" +  OLD_COMMENT_NEXT_SYMBOL + OLD_COMMENT_CLOSING_BRACKET;
				newRecord.lineNum = lineNum;
				push(top, newRecord);
			}
			break;
		default:
			break;
		}
	}
}
