#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "Enum.h"
#include "vector"

using std::vector;
using std::string;

string gtf(int num)
{
	string result;
	while (num > 0)
	{
		result.push_back('0' + (num % 10));
		num /= 10;
	}

	std::reverse(result.begin(), result.end());
	return result;
}

class Pointer
{
private:
	vector<size_t> labels;
	vector<size_t> funcers;
	vector<string> name_;
	vector<List*> where_;
	vector<size_t> num_;
	vector<size_t> variables;
	FILE* file;
	size_t F = 1;
	size_t L = 1;

public:
	bool push_file(FILE* file);
	string Dual_DASM(string word);
	bool push_point_begin(char* Ws, vector<size_t>& place, size_t num);
	bool push_do(string word, List* List);
	bool push_do_begin(char* Ws, vector<size_t>&place, List* list);
	string push_point(string word, size_t num);
	string push_var(size_t num);
	string return_var(int tmp);
	string names_(size_t i);
	List* lists_(size_t i);

	int size() const { return name_.size(); }
	void print() const;
};

bool Pointer::push_point_begin(char* Ws, vector<size_t>& place, size_t num)
{
	size_t length = place.size();
	for (size_t i = 0; i < length; i++)
	{
		if (place[i] == num + 1)
		{
			int a = i;
			length = num_.size();
			string W = Ws;
			for (size_t i = 0; i < length; i++)
			{
				if (num_[i] == num + 1)
				{
					name_[i] = (W + gtf(a + 1) + "\n");
				}
			}
			return true;
		}
	}
	place.push_back(num + 1);
	return true;
}

string Pointer::push_point(string word, size_t num)
{
	if (word == gtf(LABEL))
	{
		if (push_point_begin("L", labels, num))
		{
			word = "label L";
			L++;
			return (word + gtf(L - 1) + "\n");
		}
		else return "0";
	}
	if (word == gtf(FUNC))
	{
		if (push_point_begin("F", funcers, num))
		{
			word = "func F";
			F++;
			return (word + gtf(F - 1) + "\n");
		}
		else return "0";
	}
	else return "0";
}

bool Pointer::push_do_begin(char* Ws, vector<size_t>&place, List* list)
{
	int a;
	if (fscanf(file, "%d", &a) != 0)
	{
		int length = place.size();
		for (size_t i = 0; i < length; i++)
		{
			if (place[i] == a)
			{
				string W = Ws;
				name_.push_back(W + gtf(i + 1) + "\n");
				where_.push_back(list);
				num_.push_back(a);
				return true;
			}
		}
		string W = "X";
		place.push_back(a);
		name_.push_back(W);
		where_.push_back(list);
		num_.push_back(a);
		return true;
	}
}

bool Pointer::push_do(string word, List* list)
{
	if ((word == "jmp ") || (word == "ja ") || (word == "jb ")\
		|| (word == "jnb ") || (word == "jne ") || (word == "je ") || (word == "jna "))
	{
		if (push_do_begin("L", labels, list))
			return true;
		else
		{
			printf("Error push do\n");
			return false;
		}
	}
	if ((word == "call ") || (word == "calla ") || (word == "callna ") || (word == "callb ") || \
		(word == "callnb ") || (word == "calle ") || (word == "callne "))
	{
		if (push_do_begin("F", funcers, list))
			return true;
		else
		{
			printf("Error push do\n");
			return false;
		}
	}
	else
	{
		printf("Error - push_do - read\n");
		return false;
	}
}

string Pointer::push_var(size_t num)
{
	size_t length = variables.size();
	for (size_t i = 0; i < length; i++)
	{
		if (variables[i] == num)
		{
			printf("Error - push var\n");
			return "0";
		}
	}
	variables.push_back(num);
	string word = "var V";
	return word + gtf(length + 1) + "\n";
}

string Pointer::return_var(int tmp)
{
	int length = variables.size();
	for (size_t i = 0; i < length; i++)
	{
		if (tmp == variables[i])
		{
			string word = "V";
			tmp = i;
			return (word + gtf(i+1));
		}
	}
	printf("Error - var not founded\n");
	return "0";
}

string Pointer::names_(size_t i)
{
	if (i < size())
	{
		return name_[i];
	}
	else
	{
		fprintf(stderr, "Index out of range\n");
		getch();
	}
}

List* Pointer::lists_(size_t i)
{
	if (i < size())
	{
		List* tmp = where_[i];
		if (tmp)
		{
			return tmp;
		}
		else
		{
			fprintf(stderr, "You have bad label\n");
			return tmp;
		}
	}
	else
	{
		fprintf(stderr, "Error - lists %d\n", i);
		getch();
	}
}

bool Pointer::push_file(FILE* file_)
{
	file = file_;
	return true;
}