#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "List.h"
#include "Data.h"
#include "Enum.h"
#include "algorithm" //reverse

const int MAX_CMD_SIZE = 16;
const int MAX_PATH_SIZE = 128;
const int SUCCESS = 100500;

size_t num;

#define CHECK_CMD(STR, CONST) if(STR == word) { (word = getStrFromNumber(CONST) + " "); num++; return word; } 
#define COMMANDS_TO_JMP(STR, CONST) if(STR == word) { word = getStrFromNumber(CONST) + " "; num++; Marker(list, num); return word;}

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
	string Jumper(string word, List* List, size_t num);
	bool Marker(List* List, size_t num);
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

const char* Files()
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
		scanf("%s", word);
		fprintf(stderr, "Scanf has read: %s\n", word);//Waaagh!
		getch();
		if ("exit" == word)
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
			fprintf(stderr, "It's not a command. Start again\nYou can press exit or ignore this problem\n", word);
			getch();
		}
	}
	head_->print();
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
	CHECK_CMD("sin", SIN);
	CHECK_CMD("cos", COS);
	CHECK_CMD("hmd", HMD);
	CHECK_CMD("add", ADD);
	CHECK_CMD("pop", POP);
	CHECK_CMD("div", DIV);
	CHECK_CMD("sqrt", SQRT);
	CHECK_CMD("sum", SUM);
	CHECK_CMD("sub", SUB);
	if (word == "push")
	{
		word = Pusher();
		if (word != "0")
		{
			num++;
			return word;
		}
		else return false;
	}
	if ((word == "ja") || (word == "jb")) //etc
	{
		word = (Jumper(word, head_, num));
		if (word != "0")
		{
			num++;
			return word;
		}
		else return false;
	}
	else
	{
		return false;
	}
}

int doNothing() //The most optimistic function ever
{
	return SUCCESS;
}

string ASM::Pusher()
{
	string this_word;
	scanf("%s", this_word);

	if (IsItNumber(this_word))
	{
		fprintf(stderr, "Scanf has read: %s\n", this_word);
		getch();
		return(this_word = (getStrFromNumber(PUSH) + " " + this_word + " "));
	}
	this_word = CommandsCPU(this_word);
	if (this_word != "0")
	{
		fprintf(stderr, "Scanf has read: %s\n", this_word);
		getch();
		return this_word;
	}
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
	}
}

string CommandsCPU(string word)
{
	CHECK_CMD("cx", PUSH_CX)
	CHECK_CMD("ax", PUSH_AX)
	CHECK_CMD("dx", PUSH_DX)
	CHECK_CMD("bx", PUSH_BX)
	return false;
}

string ASM::Jumper(string word, List* list, size_t num)
{
	COMMANDS_TO_JMP("ja", JA)

	return false;
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

bool ASM::Marker(List* list, size_t num)
{
	string this_word;
	scanf("%s", this_word);

	if (this_word[0] == ':')
	{
		this_word.erase(this_word.begin());
		data_.push_begin(this_word, list);
		return true;
	}
	if (this_word.back() == ':')
	{
		this_word.pop_back();
		data_.push_end(this_word, num);
		return true;
	}
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
	}
}