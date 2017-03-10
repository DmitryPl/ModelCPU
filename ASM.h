#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include <iostream>
#include "List.h"
#include "Data.h"
#include "Enum.h"
#include "algorithm" //reverse

const int MAX_CMD_SIZE = 16;
const int MAX_PATH_SIZE = 128;
const int SUCCESS = 100500;

size_t num;

using std::string;

class ASM
{
private:
	data data_;
	List* head_;
public:

	explicit ASM()
	{
		head_ = nullptr;
	}

	bool Assembler();
	string Commands(string word);
	bool Push(List* List);
	const char* Dialog();
	const char* Files();
	string Pusher();
	string Jumper(string word, List* List);
	bool Marker(string word, List* List);
};

bool IsItNumber(string word);
int  doNothing();
string CommandsCPU(string word);
string getStrFromNumber(int num);

const char* ASM::Dialog()
{
	char a[MAX_CMD_SIZE] = "output.txt";
	const char* b;
	printf("If you want to work with files enter \"file\". If you want to enter commands from console enter \"in\".\n");
	char request[MAX_CMD_SIZE] = "";
	scanf("%s", request);
	if (strcmp("file", request) == 0)
	{
		b = Files();
		Assembler();
		head_->print();
		fprintf(stderr, "%d", num, "\n");
		getch();
		return b;
	}
	else if (strcmp("in", request) == 0)
	{
		if (!freopen("output.txt", "w", stdout))
		{
			printf("Error - ASM - In\n");
			return false;
		}
		fprintf(stderr, "Enter commands\n", "w");
		while (true)
		{
			if (Assembler())
			{
				doNothing();
			}
			else
			{
				head_->print();
				fprintf(stderr, "%d", num);
				fprintf(stderr, "\n");
				getch();
				return false;
			}
		}
		return a;
	}
	else
	{
		printf("Error - ASM - else\n");
		return false;
	}
}

const char* ASM::Files()
{
	char input[MAX_PATH_SIZE] = "";
	char output[MAX_PATH_SIZE] = "";
	printf("Enter \"S S\" to use standart files of input and output or enter way to directory like \"D:\\input.txt D:\\output.txt\"\n");
	scanf("%s %s", input, output);

	const char*  input_path = strcmp("S", input) ? input : "input.txt";
	const char* output_path = strcmp("S", output) ? output : "output.txt";

	if (!freopen(input_path, "r", stdin) || !freopen(output_path, "w", stdout))
	{
		printf("Error opening files\n");
	}
	return output_path;
}

bool ASM::Assembler()
{
	while (!feof(stdin))
	{
		string word;
		std::cin >> word;
		fprintf(stderr, "Cin \"Assembler\" has read: %s\n", word.c_str());

		if (word == "exit")
		{
			return false;
		}
		word = Commands(word);
		if (word != "0")
		{
			head_ = (head_) ? head_->push(word) : new List(word);
		}
		else
		{
			fprintf(stderr, "It's not a command. Start again\nYou can press exit or ignore this problem(if you are using the console)\n", word.c_str());
		}
	}
	for (size_t i = 0; i < data_.size(); i++)
	{
		List* tmp = data_.lists(i);
		tmp->write(getStrFromNumber(data_.numbers(i)));
	}
	return false;
}

bool IsItNumber(string word)
{
	size_t i = 0;
	while (word[i] != '\0')
	{
		if (!isdigit(word[i++]))
			return false;
	}
	return true;
}

string ASM::Commands(string word)
{
	CHECK_CMD("sin", SIN)
	CHECK_CMD("cos", COS)
	CHECK_CMD("hmd", HMD)
	CHECK_CMD("add", ADD)
	CHECK_CMD("pop", POP)
	CHECK_CMD("div", DIV)
	CHECK_CMD("sqrt", SQRT)
	CHECK_CMD("sum", SUM)
	CHECK_CMD("sub", SUB)
	if (word == "push")
	{
		word = Pusher();
		if (word != "0")
		{
			num++;
			return word;
		}
		else return "0";
	}
	if ((word == "ja") || (word == "jb") || (word == "jmp")) //etc
	{
		word = (Jumper(word, head_));
		if (word != "0")
		{
			num++;
			return word;
		}
		else return "0";
	}
	else
	{
		return "0";
	}
}

int doNothing() //The most optimistic function ever
{
	return SUCCESS;
}

string ASM::Pusher()
{
	string this_word;
	std::cin >> this_word;
	fprintf(stderr, "Cin \"Pusher\" has read: %s\n", this_word.c_str());

	if (IsItNumber(this_word))
	{
		return(this_word = (getStrFromNumber(PUSH) + " " + this_word));
	}
	this_word = CommandsCPU(this_word);
	if (this_word != "0")
	{
		return this_word;
	}
	else
	{
		fprintf(stderr, "But,...\n");
		return "0";
	}
}

string CommandsCPU(string word)
{
	CHECK_CMD("cx", PUSH_CX)
	CHECK_CMD("ax", PUSH_AX)
	CHECK_CMD("dx", PUSH_DX)
	CHECK_CMD("bx", PUSH_BX)
	return "0";
}

string ASM::Jumper(string word, List* list)
{
	COMMANDS_TO_JMP("ja", JA)
	COMMANDS_TO_JMP("jp", JP)
	COMMANDS_TO_JMP("jmp", JMP)
	return "0";
}

string getStrFromNumber(int num)
{
	string result;
	while (num > 0)
	{
		result.push_back('0' + (num % 10));
		num /= 10;
	}

	std::reverse(result.begin(), result.end());
	return result;
}

bool ASM::Marker(string word, List* list)
{
	string this_word;
	std::cin >> this_word;

	if (word == "jmp")
	{
		fprintf(stderr, "Cin \"Marker - jmp\" has read: %s\n", this_word.c_str());
		if (this_word.back() == ':')
		{
			this_word.pop_back();
			data_.push_end(this_word, num);
			return true;
		}
		else return false;
	}
	if ((word == "ja") || (word == "jp"))
	{
		fprintf(stderr, "Cin \"Marker - jx\" has read: %s\n", this_word.c_str());
		if (this_word[0] == ':')
		{
			this_word.erase(this_word.begin());
			data_.push_begin(this_word, list);
			return true;
		}
		else return false;
	}
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
		return false;
	}
}
