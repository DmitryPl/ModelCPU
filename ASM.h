#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "iostream"
#include "List.h"
#include "Data.h"
#include "Enum.h"
#include "algorithm"

using std::string;

class ASM
{
private:
	data data_;
	data Func_;
	List* head_;
	size_t num;

	string Commands(string word);
	bool Push(List* List);
	string Pusher();
	string Poper();
	string Iner();
	string Jumper(string word, List* List);
	string Funcer(string word, List* List);
	bool Marker(string word, List* List);
	bool Marker_F(string word, List* List);
	string CommandsCPUpush(string word);
	string CommandsCPUpop(string word);
	string CommandsCPUin(string word);
	bool Ending();
	const char* Files();
	bool Assembler();
	void Help();

public:
	const char* Dialog();

	explicit ASM()
	{
		head_ = nullptr;
		num = 0;
	}

};

const char* ASM::Dialog()
{
	fprintf(stderr, "\nSTARTING ASM\n\n");
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
		fprintf(stderr, "\nNumber of commands: %d", num);
		fprintf(stderr, "\n...\n");
		printf("%d", HMD);
		fprintf(stderr, "\nENDING ASM\n");
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
				fprintf(stderr, "Number of commands: %d", num);
				fprintf(stderr, "\n...\n");
				return false;
			}
		}
		fprintf(stderr, "\nENDING ASM\n");
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

void ASM::Help()
{
	fprintf(stderr, HELP);
	fprintf(stderr, "\n");
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
			if (Ending())
			{
				return false;
			}
			else
				assert("ASM - Ending - False Label", false);
		}
		if (word == "help")
		{
			Help();
		}
		else
		{
			head_ = (head_) ? head_->push() : new List();
			word = Commands(word);
			if (word != "0")
			{
				head_->pusher(word);
				/*if (head_)
				{
				head_ = head_->push(word);
				assert(head_);
				std::cerr << "New head is " << head_ << "[" << word << "] and next is " << head_->get_next() << "[" << head_->get_next()->get_word() << "]\n";
				std::cerr << "SIZE: " << head_->get_size() << "\n";
				getch();
				}
				else
				{
				head_ = new List(word);
				assert(head_);
				std::cerr << "New head is " << head_ << "[" << word << "] and next is NULL\n";
				std::cerr << "SIZE: " << head_->get_size() << "\n";
				getch();
				}*/
			}
			else
			{
				getch();
				fprintf(stderr, "It's not a command. Start again\nYou can press exit or ignore this problem(if you are using the console)\n", word.c_str());
			}
		}
	}
	if (Ending())
	{
		return false;
	}
	else
		assert("ASM - Ending - False Label", false);
}

string ASM::Commands(string word)
{
	CHECK_CMD("sin", SIN)
	CHECK_CMD("cos", COS)
	CHECK_CMD("hmd", HMD)
	CHECK_CMD("add", ADD)
	CHECK_CMD("div", DIV)
	CHECK_CMD("sqrt", SQRT)
	CHECK_CMD("sum", SUM)
	CHECK_CMD("sub", SUB)
	CHECK_CMD("out", OUT)
	CHECK_CMD("dec", DEC)
	CHECK_CMD("ded", DED)
	CHECK_CMD("inc", INC)
	CHECK_CMD("ret", RET)
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
	if (word == "pop")
	{
		word = Poper();
		if (word != "0")
		{
			num++;
			return word;
		}
		else return "0";
	}
	if (word == "in")
	{
		word = Iner();
		if (word != "0")
		{
			num++;
			return word;
		}
		else return "0";
	}
	if ((word == "ja") || (word == "jb") || (word == "jmp") || (word == "label") || (word == "jc"))
	{
		word = (Jumper(word, head_));
		if (word != "0")
		{
			return word;
		}
		else return "0";
	}
	if ((word == "func") || (word == "calla") || (word == "callc") || (word == "callp") || (word == "ret"))
	{
		word = (Funcer(word, head_));
		if (word != "0")
		{
			return word;
		}
		else return "0";
	}
	else
	{
		return "0";
	}
}

string ASM::Poper()
{
	string this_word;
	std::cin >> this_word;
	fprintf(stderr, "Cin \"Pop\" has read: %s\n", this_word.c_str());

	this_word = CommandsCPUpop(this_word);
	if (this_word != "0")
	{
		num--;
		return this_word;
	}
	else
	{
		fprintf(stderr, "But,...\n");
		return "0";
	}
}

string ASM::Iner()
{
	string this_word;
	std::cin >> this_word;
	fprintf(stderr, "Cin \"Pop\" has read: %s\n", this_word.c_str());

	this_word = CommandsCPUin(this_word);
	if (this_word != "0")
	{
		num--;
		return this_word;
	}
	else
	{
		fprintf(stderr, "But,...\n");
		return "0";
	}
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
	this_word = CommandsCPUpush(this_word);
	if (this_word != "0")
	{
		num--;
		return this_word;
	}
	else
	{
		fprintf(stderr, "But,...\n");
		return "0";
	}
}

string ASM::CommandsCPUpush(string word)
{
	CHECK_CMD("cx", PUSH_CX)
	CHECK_CMD("ax", PUSH_AX)
	CHECK_CMD("dx", PUSH_DX)
	CHECK_CMD("bx", PUSH_BX)
	return "0";
}

string ASM::CommandsCPUpop(string word)
{
	CHECK_CMD("cx", POP_CX)
	CHECK_CMD("ax", POP_AX)
	CHECK_CMD("dx", POP_DX)
	CHECK_CMD("bx", POP_BX)
	return "0";
}

string ASM::CommandsCPUin(string word)
{
	CHECK_CMD("cx", IN_CX)
	CHECK_CMD("ax", IN_AX)
	CHECK_CMD("dx", IN_DX)
	CHECK_CMD("bx", IN_BX)
	return "0";
}

string ASM::Jumper(string word, List* list)
{
	COMMANDS_TO_JMP("ja", JA)
	COMMANDS_TO_JMP("jp", JP)
	COMMANDS_TO_JMP("jc", JC)
	COMMANDS_TO_JMP("label", LABEL)
	COMMANDS_TO_JMP("jmp", JMP)
	return "0";
}

string ASM::Funcer(string word, List* list)
{
	COMMANDS_TO_JMP_F("calla", CALLA)
	COMMANDS_TO_JMP_F("callc", CALLC)
	COMMANDS_TO_JMP_F("callp", CALLP)
	COMMANDS_TO_JMP_F("func", FUNC)
	return "0";
}

bool ASM::Marker_F(string word, List* list)
{
	string this_word;
	std::cin >> this_word;
	if ((word == "calla") || (word == "callc") || (word == "callp"))
	{
		fprintf(stderr, "Cin \"Marker - jx\" has read: %s\n", this_word.c_str());
		if (this_word.back() == ':')
		{
			this_word.pop_back();
			if (Func_.push_jx(this_word, list, num))
			{
				doNothing();
				return true;
			}
			else
			{
				fprintf(stderr, "\nError - Marker\n");
				return false;
			}
		}
		else return false;
	}
	if (word == "func")
	{
		fprintf(stderr, "Cin \"Marker - label\" has read: %s\n", this_word.c_str());
		if (this_word[0] == ':')
		{
			this_word.erase(this_word.begin());
			if (Func_.push_label(this_word, num))
			{
				doNothing();
				return true;
			}
			else
			{
				fprintf(stderr, "\nError - Marker\n");
				return false;
			}
		}
		else return false;
	}
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
		return false;
	}
}

bool ASM::Marker(string word, List* list)
{
	string this_word;
	std::cin >> this_word;
	if ((word == "ja") || (word == "jp") || (word == "jc") || (word == "jmp"))
	{
		fprintf(stderr, "Cin \"Marker - jx\" has read: %s\n", this_word.c_str());
		if (this_word.back() == ':')
		{
			this_word.pop_back();
			if (data_.push_jx(this_word, list, num))
			{
				doNothing();
				return true;
			}
			else
			{
				fprintf(stderr, "\nError - Marker\n");
				return false;
			}
		}
		else return false;
	}
	if (word == "label")
	{
		fprintf(stderr, "Cin \"Marker - label\" has read: %s\n", this_word.c_str());
		if (this_word[0] == ':')
		{
			this_word.erase(this_word.begin());
			if (data_.push_label(this_word, num))
			{
				doNothing();
				return true;
			}
			else
			{
				fprintf(stderr, "\nError - Marker\n");
				return false;
			}
		}
		else return false;
	}
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
		return false;
	}
}

bool ASM::Ending()
{
	for (size_t i = 0; i < data_.size(); i++)
	{
		fprintf(stderr, "\n");
		List* tmp1 = data_.lists_jx(i);
		if (tmp1)
		{
			tmp1->write(getStrFromNumber(data_.numbers_jx(i)));
		}
		else
		{
			fprintf(stderr, "Error - Ending - wrong label\n");
			return false;
		}
	}
	for (size_t i = 0; i < Func_.size(); i++)
	{
		fprintf(stderr, "\nfor!!!\n");
		List* tmp1 = Func_.lists_jx(i);
		if (tmp1)
		{
			tmp1->write(getStrFromNumber(Func_.numbers_jx(i)));
		}
		else
		{
			fprintf(stderr, "Error - Ending - wrong label\n");
			return false;
		}
	}
	return true;
}
