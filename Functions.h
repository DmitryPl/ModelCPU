#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "vector"
#include "Enum.h"

using std::vector;

class Functions
{
private:
	vector<MyFuncType> data_;
	vector<int> numbers_;
	vector<size_t> where_;

public:
	int size_type() const { return this->data_.size(); }
	bool empty_type() const { return this->data_.size() == 0; }
	int size_number() const { return this->numbers_.size(); }
	bool empty_number() const { return this->numbers_.size() == 0; }
	MyFuncType do_(int i) const;
	void print() const;

	void write_numbers(size_t num_of_com, int num);
	int return_numbers(size_t num_of_com);
	void push(MyFuncType Func);
	void write(MyFuncType Func);
};

MyFuncType Functions::do_(int i) const
{
	return data_[i];
}

void Functions::write(MyFuncType Func)
{
	if (data_.size() - 1)
	{
		data_[data_.size() - 1] = Func;
	}
	else
	{
		printf("Error - write - functions\n");
	}
}

void Functions::push(MyFuncType Func)
{
	data_.push_back(Func);
}

void Functions::write_numbers(size_t num_of_com, int num)
{
	numbers_.push_back(num);
	where_.push_back(num_of_com);
}

int Functions::return_numbers(size_t num_of_com)
{
	for (size_t i = 0; i < where_.size(); i++)
	{
		if (num_of_com == where_[i])
		{
			return numbers_[i];
		}
	}
	return NAN;
}

void Functions::print() const
{
	for (size_t i = 0; i < numbers_.size(); i++)
	{
		fprintf(stderr, "%d ", numbers_[i]);
	}
	fprintf(stderr, "\n");
	for (size_t i = 0; i < where_.size(); i++)
	{
		fprintf(stderr, "%d ", where_[i]);
	}
	fprintf(stderr, "\n");
}