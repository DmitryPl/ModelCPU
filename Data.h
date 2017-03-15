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
	vector<size_t> number_jx;
	vector<size_t> number_label;
	vector<string> name_;
	vector<List*> where_label;
	vector<List*> where_jx;

public:
	bool push_jx(string word, List* List, size_t num);
	bool push_label(string word, List* List, size_t num);
	size_t numbers_jx(size_t i);
	size_t numbers_label(size_t i);
	List* lists_jx(size_t i);
	List* lists_label(size_t i);

	void print() const;
	size_t size() const { return name_.size(); }
};

bool data::push_jx(string word, List* list, size_t num)
{
	fprintf(stderr, "push_jx\n");
	fprintf(stderr, "%s \n", word.c_str());
	int a = 0;
	if (!list && !this)
	{
		fprintf(stderr, "error - push_jx\n");
		return false;
	}
	if (name_.size() != 0)
	{
		for (size_t i = 0; i < name_.size(); i++)
		{
			if (word == name_[i])
			{
				/*if (number_label[i] != -1)
				{
					fprintf(stderr, "Error - Overwriting of label!");
					return false;
				}*/
				number_label[i] = (num + 1);
				where_jx[i] = list;
				int a = 1;
				return true;
			}
		}
		name_.push_back(word);
		number_label.push_back(num + 1);
		where_jx.push_back(list);
		number_jx.push_back(num + 1);
		where_label.push_back(list);
		return true;
	}
	else
	{
		name_.push_back(word);
		number_label.push_back(num + 1);
		where_jx.push_back(list);
		number_jx.push_back(-1);
		where_label.push_back(nullptr);
		return true;
	}
}

bool data::push_label(string word, List* List, size_t num)
{
	fprintf(stderr, "push_label\n");
	fprintf(stderr, "%s \n", word.c_str());
	int a = 0;
	if (!List && !this)
	{
		fprintf(stderr, "error - push_label\n");
		return false;
	}
	if (name_.size() != 0)
	{
		for (size_t i = 0; i < name_.size(); i++)
		{
			if (word == name_[i])
			{
				/*if (number_jx[i] != -1)
				{
					fprintf(stderr, "Error - Overwriting of jx!");
					return false;
				}*/
				number_jx[i] = (num + 1);
				where_label[i] = List;
				return true;
			}
		}
		name_.push_back(word);
		number_jx.push_back(num + 1);
		where_label.push_back(List);
		number_label.push_back(- 1);
		where_jx.push_back(nullptr);
		return true;
	}
	else
	{
		name_.push_back(word);
		number_jx.push_back(num + 1);
		where_label.push_back(List);
		number_label.push_back(-1);
		where_jx.push_back(nullptr);
		return true;
	}
}

size_t data::numbers_jx(size_t i)
{
	if (i < name_.size())
	{
		fprintf(stderr, "numbers_jx: %d\n", number_jx[i]);
		return number_jx[i];
	}
	else
	{
		fprintf(stderr, "Index out of range\n");
		getch();
	}
}

List* data::lists_jx(size_t i)
{
	if (i < name_.size())
	{
		List* tmp = where_jx[i];
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

size_t data::numbers_label(size_t i)
{
	if (i < name_.size())
	{
		fprintf(stderr, "numbers_label: %d\n", number_label[i]);
		return number_label[i];
	}
	else
	{
		fprintf(stderr, "Index out of range\n");
		getch();
	}
}

List* data::lists_label(size_t i)
{
	if (i < name_.size())
	{
		List* tmp = where_label[i];
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

void data::print() const
{
	for (size_t i = 0; i < number_jx.size(); i++)
	{
		fprintf(stderr, "%d ", number_jx[i]);
	}
	fprintf(stderr, "\n");
	for (size_t i = 0; i < name_.size(); i++)
	{
		fprintf(stderr, "%s ", name_[i].c_str());
	}
	fprintf(stderr, "\n");
	for (size_t i = 0; i < number_label.size(); i++)
	{
		fprintf(stderr, "%d ", number_label[i]);
	}
}
