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

class Variable
{
private:
	vector<size_t> number_var;
	vector<size_t> number_decl;
	vector<string> name_decl;
	vector<List*> where_var;

public:
	bool push_var(string word, List* List);
	bool push_decl(string word, size_t num);
	size_t numbers_(size_t i);
	List* lists_(size_t i);
	int IsItVariable(string word);

	void print() const;
	size_t  size() const { return this->number_var.size(); }
};

bool Variable::push_var(string word, List* list)
{
	if (!list && !this)
	{
		fprintf(stderr, "error - push_var - error\n");
		return false;
	}
	size_t length = name_decl.size();
	for (size_t i = 0; i < length; i++)
	{
		if (word == name_decl[i])
		{
			where_var.push_back(list);
			number_var.push_back(number_decl[i]);
			return true;
		}
	}
	fprintf(stderr, "error - not declarated - push_var\n");
	return false;
}

bool Variable::push_decl(string word, size_t num)
{
	if (!this)
	{
		fprintf(stderr, "error - push_decl - error\n");
		return false;
	}
	size_t length = name_decl.size();
	for (size_t i = 0; i < length; i++)
	{
		if (word == name_decl[i])
		{
			fprintf(stderr, "error - push_decl - it was declarated\n");
			return false;
		}
	}
	name_decl.push_back(word);
	number_decl.push_back(num);
	return true;
}

size_t Variable::numbers_(size_t i)
{
	if (i < number_var.size())
	{
		return number_var[i];
	}
	else
	{
		fprintf(stderr, "Index out of range - var\n");
	}
}

List* Variable::lists_(size_t i)
{
	if (i < number_var.size())
	{
		return where_var[i];
	}
	else
	{
		fprintf(stderr, "Error - lists - var%d\n", i);
	}
}

int Variable::IsItVariable(string word)
{
	size_t length = name_decl.size();
	for (size_t i = 0; i < length; i++)
	{
		if (word == name_decl[i])
		{
			return number_decl[i] + 1;
		}
	}
	return -1;
}

void Variable::print() const
{
	size_t length = number_decl.size();
	fprintf(stderr, "number_decl: ");
	for (size_t i = 0; i < length; i++)
	{
		fprintf(stderr, "%d ", number_decl[i]);
	}
	fprintf(stderr, "\n");
	length = name_decl.size();
	fprintf(stderr, "name_decl: ");
	for (size_t i = 0; i < length; i++)
	{
		fprintf(stderr, "%d ", name_decl[i].c_str());
	}
	fprintf(stderr, "\n");
	length = number_var.size();
	fprintf(stderr, "number_var: ");
	for (size_t i = 0; i < length; i++)
	{
		fprintf(stderr, "%s ", number_var[i]);
	}
	fprintf(stderr, "\n");
}
