// Кублицкая Анна Виталия, ПС-21
/* В   некотором   компиляторе   ПАСКАЛя  текст  программы
включает примечания,  выделенные  фигурными  скобками  '{','}'
либо  парами  символов  '(*'  и  '*)'.  Примечания  могут быть
вложенными друг в друга.  Если примечание открыто знаком  '{',
то оно должно быть закрыто знаком '}'.  Аналогично примечание,
начинающееся с символов '(*'  должно  заканчиваться  символами
'*)'. Требуется:
   1) проверить правильность вложенности примечаний;
   2) переписать   файл   с   исходным   текстом   так,  чтобы
отсутствовала  вложенность  комментариев  при  сохранении   их
содержания  и  в  качестве  ограничивающих  символов  остались
только  фигурные  скобки.   Учесть   случай,   когда   символы
примечаний находятся в апострофах (10).*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CharStack final
{
	struct stack
	{
		char key;
		stack * next;
	};
public:
	void NewStack();
	bool Push(char symbol);
	string Top();
	string Pop();
	bool isOverflow();
private:
	stack * top = new stack;
	int overflowController = 0;
	const int MAX_SIZE = 100;
};

bool CharStack::Push(char symbol)
{
	stack * temp = new stack;
	temp->key = symbol;
	temp->next = top;
	top = temp;
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: commentControl.exe <input file><output file>";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	string programmString;

	while (getline(input, programmString))
	{
		output << stringToChange + '\n';
	}

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}