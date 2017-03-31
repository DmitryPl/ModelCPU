#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "vector"
#include "Enum.h"

using std::vector;

class DualType
{
private:
	vector<size_t> where_;
	vector<char> flag_com_1;
	vector<size_t> com_1;
	vector<char> flag_com_2;
	vector<size_t> com_2;

public:
	int size() const { return this->where_.size(); }
	bool empty() const { return this->where_.size() == 0; }
	void print() const;
	int return_place(size_t num_of_com);
	void push(size_t place, char flag1, size_t com1, char flag2, size_t com2);
};

void DualType::print() const
{
	size_t length = where_.size();
	printf("where_: ");
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", where_[i]);
	}
	printf("\n");
	printf("flag 1: ");
	length = flag_com_1.size();
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", flag_com_1[i]);
	}
	printf("\n");
	printf("com1: ");
	length = com_1.size();
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", com_1[i]);
	}
	printf("flag 2: ");
	length = flag_com_2.size();
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", flag_com_2[i]);
	}
	printf("\n");
	printf("com2: ");
	length = com_2.size();
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", com_1[i]);
	}
	printf("\n");
}

void DualType::push(size_t place, char flag1, size_t com1, char flag2, size_t com2)
{
	where_.push_back(place);
	flag_com_1.push_back(flag1);
	com_1.push_back(com1);
	flag_com_2.push_back(flag2);
	com_2.push_back(com2);
}
/*
int DualType::return_com(size_t num_of_com)
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
	if (i != -1)
	{
		return numbers_[i];
	}
	else
	{
		printf("Error - ret num!!!!\n");
		return false;
	}
}*/

int DualType::return_place(size_t num_of_com)
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