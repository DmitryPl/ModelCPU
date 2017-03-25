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
using std::find;

class data
{
private:
	vector<size_t> number_jx;
	vector<size_t> number_label;
	vector<string> name_label;
	vector<string> name_jx;
	vector<List*> where_jx;

public:
	bool push_jx(string word, List* List, size_t num);
	bool push_label(string word, size_t num);
	size_t numbers_jx(size_t i);
	List* lists_jx(size_t i);

	void print() const;
	size_t  size() const { return this->name_jx.size(); }
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
	if (name_label.size() != 0)
	{
		//auto result = find(name_label.begin(), name_label.end(), word);
		for (size_t i = 0; i < name_label.size(); i++)
		{
			if (word == name_label[i])
			{
				number_jx.push_back(number_label[i]);
				where_jx.push_back(list);
				name_jx.push_back(word);
				return true;
			}
		}
		name_label.push_back(word);
		name_jx.push_back(word);
		number_label.push_back(-1);
		where_jx.push_back(list);
		number_jx.push_back(-1);
		return true;
	}
	else
	{
		name_label.push_back(word);
		name_jx.push_back(word);
		number_label.push_back(-1);
		where_jx.push_back(list);
		number_jx.push_back(-1);
		return true;
	}
}

bool data::push_label(string word, size_t num)
{
	fprintf(stderr, "push_label\n");
	fprintf(stderr, "%s \n", word.c_str());
	int a = 0;
	if (!this)
	{
		fprintf(stderr, "error - push_label\n");
		return false;
	}
	if (name_label.size() != 0)
	{
		for (size_t i = 0; i < name_label.size(); i++)
		{
			if (word == name_label[i])
			{
				if (number_label[i] == -1)
				{
					number_label[i] = num + 1;
					for (size_t i = 0; i < name_jx.size(); i++)
					{
						if (word == name_jx[i])
						{
							number_jx[i] = num + 1;
						}
					}
				}
				else
				{
					fprintf(stderr, "there is other label with this name!\n");
					return false;
				}
			}
		}
		name_label.push_back(word);
		number_label.push_back(num + 1);
		return true;
	}
	else
	{
		name_label.push_back(word);
		number_label.push_back(num + 1);
		return true;
	}
}

size_t data::numbers_jx(size_t i)
{
	if (i < name_jx.size())
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
	if (i < name_jx.size())
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

void data::print() const
{
	for (size_t i = 0; i < number_jx.size(); i++)
	{
		fprintf(stderr, "%d ", number_jx[i]);
	}
	fprintf(stderr, "\n");
	for (size_t i = 0; i < name_jx.size(); i++)
	{
		fprintf(stderr, "%d ", name_jx[i]);
	}
	fprintf(stderr, "\n");
	for (size_t i = 0; i < name_label.size(); i++)
	{
		fprintf(stderr, "%s ", name_label[i].c_str());
	}
	fprintf(stderr, "\n");
	for (size_t i = 0; i < number_label.size(); i++)
	{
		fprintf(stderr, "%d ", number_label[i]);
	}
}
