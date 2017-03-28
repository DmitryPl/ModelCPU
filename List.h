#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "iostream"
#include "Enum.h"

using std::string;

class List
{
private:
	string word_;
	class List *next;

public:
	List* push(string word);
	List* push();
	~List();

	explicit List(string word) :
		word_(word),
		next(nullptr)
	{}

	explicit List() :
		word_(),
		next(nullptr)
	{}

	void write(string word);
	void pusher(string word);
	bool empty() const { return false; }
	void print();
	List* get_next() const { return next; }
	void delete_last() const;
	string get_word() const { return word_; }
	int get_size() const { return (next ? next->get_size() : 0) + 1; }
};

List* List::push(string word)
{
	List* new_head = new List(word);
	new_head->word_ = word;
	new_head->next = this;
	return new_head;
}

List* List::push()
{
	List* new_head = new List();
	new_head->next = this;
	return new_head;
}

void List::write(string word)
{
	this->word_ += (" " + word);
}

void List::pusher(string word)
{
	this->word_ += (word);
}

void List::print()
{
	if (next != nullptr)
	{
		next->print();
	}
	printf("%s ", word_.c_str());
}

List::~List()
{
	if (next)
	    delete next;
}