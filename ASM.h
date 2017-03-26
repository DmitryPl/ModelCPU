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
	string Complicate_F(const int T1, const int T2, const int T3, const int T4, const int T5);
	string to_Marker(string word, List* list);
	bool Marker(string word, List* List, data* what);
	bool Ending();
	const char* Files();
	bool Assembler();
	void Help();
	void End();

	string CommandsCPU(string word, const int T1, const int T2, const int T3, const int T4);

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
	const char* b = "output.txt";
	printf("If you want to work with files enter \"file\". If you want to enter commands from console enter \"in\".\n");
	char request[MAX_CMD_SIZE] = "";
	scanf("%s", request);
	if (strcmp("file", request) == 0)
	{
		b = Files();
		if (b)
		{
			Assembler();
			End();
			return b;
		}
		else
		{
			return false;
		}
	}
	else if (strcmp("in", request) == 0)
	{
		if (!freopen("output.txt", "w+", stdout))
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
				End();
				return b;
			}
		}
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
		return false;
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
#define CHECK_CMD(STR, CONST) if(STR == word)\
		{ word = getStrFromNumber(CONST) ; num++; return word; }
	CHECK_CMD("sin", SIN);
	CHECK_CMD("cos", COS);
	CHECK_CMD("halt", HALT);
	CHECK_CMD("add", ADD);
	CHECK_CMD("div", DIV);
	CHECK_CMD("sqrt", SQRT);
	CHECK_CMD("mul", MUL);
	CHECK_CMD("sub", SUB);
	CHECK_CMD("out", OUT);
	CHECK_CMD("ded", DED);
	CHECK_CMD("ret", RET);
#undef CHECH_CMD

#define COMP_F(STR, ax, bx, cx, dx, con) if(STR == word)\
		{ word = Complicate_F(ax, bx, cx, dx, con); if (word != "0") { num++; return word; } else return "0"; }
	COMP_F("push", PUSH_AX, PUSH_BX, PUSH_CX, PUSH_DX, PUSH);
	COMP_F("pop" , POP_AX, POP_BX, POP_CX, POP_DX, NULL);
	COMP_F("in", IN_AX, IN_BX, IN_CX, IN_DX, IN);
	COMP_F("dec", DEC_AX, DEC_BX, DEC_CX, DEC_DX, DEC_S);
	COMP_F("inc", INC_AX, INC_BX, INC_CX, INC_DX, INC_S);
#undef COMP_F

#define JMP_ ("ja") || ("jna") || ("je") || ("jne") || ("jb") || ("jnb") || ("jmp")
#define CALL_ ("calla") || ("callna") || ("calle") || ("callne") || ("callb") || ("callnb") || ("call")

#define FUNC_JMP(DEFINE) if (word == DEFINE)\
			{ word = (to_Marker(word, head_)); if (word != "0") { return word; } else return "0"; }
	FUNC_JMP(CALL_);
	FUNC_JMP(JMP_);
#undef FUNC_JMP

	return "0";
}

string ASM::Complicate_F(const int ax, const int bx, const int cx, const int dx, const int con)
{
	string this_word;
	std::cin >> this_word;
	fprintf(stderr, "Cin \"Pusher\" has read: %s\n", this_word.c_str());

	if ((con != NULL) && IsItNumber(this_word))
	{
		return(this_word = (getStrFromNumber(con) + " " + this_word));
	}
	this_word = CommandsCPU(this_word, ax, bx, cx, dx);
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

string ASM::CommandsCPU(string word, const int ax, const int bx, const int cx, const int dx)
{
#define CHECK_CMD(STR, CONST) if(STR == word)\
		{ word = getStrFromNumber(CONST) ; num++; return word; }
	CHECK_CMD("cx", cx);
	CHECK_CMD("ax", ax);
	CHECK_CMD("dx", dx);
	CHECK_CMD("bx", bx);
#undef CHECK_CMD
	return "0";
}

string ASM::to_Marker(string word, List* list)
{
#define COMMANDS_TO_M(STR, CONST, WHAT) if(STR == word)\
	{ if(Marker(word, list, WHAT)) { word = getStrFromNumber(CONST) ; num++; return word;} else return "0"; }
	COMMANDS_TO_M("je", J_E, &data_);
	COMMANDS_TO_M("jne", J_NE, &data_);
	COMMANDS_TO_M("jb", J_B, &data_);
	COMMANDS_TO_M("jnb", J_NB, &data_);
	COMMANDS_TO_M("ja", J_A, &data_);
	COMMANDS_TO_M("jna", J_NA, &data_);
	COMMANDS_TO_M("label", LABEL, &data_);
	COMMANDS_TO_M("jmp", JMP, &data_);
	COMMANDS_TO_M("calle", CALL_E, &Func_);
	COMMANDS_TO_M("callne", CALL_NE, &Func_);
	COMMANDS_TO_M("callb", CALL_B, &Func_);
	COMMANDS_TO_M("callnb", CALL_NB, &Func_);
	COMMANDS_TO_M("calla", CALL_A, &Func_);
	COMMANDS_TO_M("callna", CALL_NA, &Func_);
	COMMANDS_TO_M("call", CALL, &Func_);
	COMMANDS_TO_M("func", FUNC, &Func_)
#undef COMMANDS_TO_M
	return "0";

}

bool ASM::Marker(string word, List* list, data* what)
{
	string this_word;
	std::cin >> this_word;
	
	if ((word == "label") || (word == "func"))
	{
		fprintf(stderr, "Cin \"Marker - declaration\" has read: %s\n", this_word.c_str());
		if (this_word[0] == ':')
		{
			this_word.erase(this_word.begin());
			if (what->push_label(this_word, num))
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
	else if (word == CALL_ || JMP_)
	{
		fprintf(stderr, "Cin \"Marker - action\" has read: %s\n", this_word.c_str());
		if (this_word.back() == ':')
		{
			this_word.pop_back();
			if (what->push_jx(this_word, list, num))
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

void ASM::End()
{
	head_->print();
	fprintf(stderr, "Number of commands: %d", num);
	fprintf(stderr, "\n...\n");
	printf("%d", HALT);
	fprintf(stderr, "\nENDING ASM\n");
}