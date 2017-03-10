#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "List.h"
#include "vector"

using std::vector;

class data
{
private:
	vector<size_t> number_;
	vector<string> name_;
	vector<List*> where_;

public:
	void push_begin(string word, List* List);
	bool push_end(string word, size_t i);
	size_t numbers(size_t i);
	List* lists(size_t i);

	size_t size() { return name_.size(); }
};


void data::push_begin(string word, List* list)
{
	name_.push_back(word);
	where_.push_back(list);
}

bool data::push_end(string word, size_t num)
{
	int a = name_.size();
	for (int i = 0; i < a; ++i)
	{
		if (word == name_[i])
		{
			number_.push_back(num);
			return true;
		}
	}
	return false;
}

size_t data::numbers(size_t i)
{
	if (i < number_.size())
	{
		return number_[i];
	}
	else
	{
		fprintf(stderr, "w", "Index out_of_range\n");
	}
}

List* data::lists(size_t i)
{
	if (i < number_.size())
	{
		return where_[i];
	}
	else
	{
		fprintf(stderr, "w", "Error - lists\n");
	}
}