#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include <iostream>
#include "Enum.h"

using std::string;

class List
{
private:
	string word_;
	class List *next;

public:
	List* push(string word);

	~List();

	explicit List(string word) :
		word_(word),
		next(nullptr)
	{}

	List* getNth(int n);
	void write(string word);
	bool empty() const { return false; }
	void print();
};

List* List::push(string word)
{
	List* new_head = new List(word);
	new_head->word_ = word;
	new_head->next = this;
	return new_head;
}

void List::write(string word)
{
	this->word_ += word;
}

/*List* List::getNth(int n)
{
int counter = 0;
while (counter < n && next)
{
head_ = head_->next; 
counter++;
}
return next;
}*/

void List::print()
{
	if (next)
	{
		printf("%s ", word_.c_str());
		next->print();
	}
}

List::~List()
{
	if (next)
		next->~List();
	delete next;
}
