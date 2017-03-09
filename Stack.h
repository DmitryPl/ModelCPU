#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

class Stack
{
private:
	int *data_;
	size_t capacity_;
	size_t size_;

public:
	void push(int value);
	int pop();

	void reserve(size_t new_capacity);
	void swap(Stack* that);
	void shrink_to_fit() { reserve(size_); }

	Stack(const Stack &that);
	~Stack();

	explicit Stack(size_t capacity = 4) :
		capacity_(capacity),
		size_(0)
	{
		this->data_ = (int*)malloc(capacity * sizeof(int));
		if (!ok())
		{
			assert((printf("ERROR-Constructor\n"), print(), false));
		}
	}

	int size() const { return this->size_; }
	int top() const { return this->data_[this->size_ - 1]; }
	bool empty() const { return this->size_ == 0; }

	bool ok() const;
	void print() const;
};

void Stack::push(int value)
{
	if (!ok())
	{
		assert(("ERROR-Push", print(), false));
	}
	if (this->size_ >= this->capacity_)
	{
		reserve(this->capacity_ * 2);
	}
	if (this->size_ == 0)
	{
		reserve(this->capacity_ + 1);
	}
	this->data_[this->size_] = value;
	this->size_++;
}

int Stack::pop()
{
	if (this->size_ == 0)
	{
		printf("No elements to pop\n Press the button to end\n");
		assert((print(), this->size_ > 0));
	}
	if (!ok())
	{
		ok();
		print();
		assert(("ERROR-Pop", false));
	}
	this->size_--;
	return (this->data_[this->size_]);
}

Stack::Stack(const Stack &that)
{
	data_ = new int[that.capacity_];
	capacity_ = that.capacity_;
	size_ = that.size_;
	for (size_t i = 0; i < size_; ++i)
	{
		data_[i] = that.data_[i];
	}
	if (!that.ok() || !ok())
	{
		assert(("ERROR-Copy", that.print(), this->ok(), this->print(), false));
	}
}

Stack::~Stack()
{
	free(this->data_);
	this->data_ = NULL;
	this->capacity_ = NULL;
	this->size_ = NULL;
}

void Stack::reserve(size_t new_capacity)
{
	this->data_ = (int*)realloc(this->data_, sizeof(int) * new_capacity);
	if (!ok())
	{
		assert(("ERROR-Reserve", print(), false));
	}
	this->capacity_ = new_capacity;
}

void Stack::swap(Stack* that)
{
	int* temp = this->data_;
	this->data_ = that->data_;
	that->data_ = temp;
	int tempar = this->capacity_;
	this->capacity_ = that->capacity_;
	that->capacity_ = tempar;
	tempar = this->size_;
	this->size_ = that->size_;
	that->size_ = tempar;
	if (!(this->ok()) && (!(that->ok())))
	{
		assert(("ERROR-swap", this->print(), that->print(), false));
	}
}

bool Stack::ok() const
{
	int i = 0;
	if (data_ < 0)
	{
		printf("Memory error\n");
		i++;
	}
	if (size_ > capacity_)
	{
		printf("Size >= Capacity\n");
		i++;
	}
	if (capacity_ < 0)
	{
		printf("Capacitry error\n");
		i++;
	}
	if (size_ < 0)
	{
		printf("Size error\n");
		i++;
	}
	return (!i);
}

void Stack::print() const
{
	printf("Printing stack: [%d/%d] \n", size_, capacity_);
	for (size_t i = 0; i < size_; ++i)
	{
		printf("%d:%d ", i + 1, this->data_[i]);
	}
	printf("\n");
}