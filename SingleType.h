#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "vector"
#include "Enum.h"

using std::vector;

class SingleType
{
private:
	vector<int> numbers_;
	vector<size_t> where_;
	vector<const int> do_;

public:
	int size() const { return this->numbers_.size(); }
	bool empty() const { return this->numbers_.size() == 0; }
	void print() const;

	void push(size_t place, int num, const int comm);
	int return_com(size_t num_of_com);
	int return_numbers(size_t num_of_com);
	int return_place(size_t num_of_com);
};

void SingleType::print() const
{
	size_t length = numbers_.size();
	printf("numbers_: ");
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", numbers_[i]);
	}
	printf("\n");
	printf("where: ");
	length = where_.size();
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", where_[i]);
	}
	printf("\n");
	printf("do: ");
	length = do_.size();
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", do_[i]);
	}
}

void SingleType::push(size_t place, int num, const int comm)
{
	where_.push_back(place);
	numbers_.push_back(num);
	do_.push_back(comm);
}

int SingleType::return_com(size_t num_of_com)
{
	int i = return_place(num_of_com);
	if (i != -1)
	{
		return do_[i];
	}
	else
	{
		printf("Error - ret num\n");
		return false;
	}
}

int SingleType::return_numbers(size_t num_of_com)
{
	int i = return_place(num_of_com);
	if (i != -1 )
	{
		return numbers_[i];
	}
	else
	{
		printf("Error - ret num!!!!\n");
		return false;
	}
}

int SingleType::return_place(size_t num_of_com)
{
	int length = where_.size();
	for (size_t i = 0; i < length; i++)
	{
		if (num_of_com = where_[i])
		{
			return i;
		}
	}
	return -1;
}