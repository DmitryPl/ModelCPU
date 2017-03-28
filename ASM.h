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
#include "Variable.h"
#include "algorithm"

using std::string;

class ASM
{
private:
	data data_;
	data Func_;
	Variable Var_;
	List* head_;
	size_t num;

	string Commands(string word);
	bool Push(List* List);
	string Complicate_F(const int ax, const int bx, const int cx, const int dx, const int con, const int var);
	string CommandsCPU(string word, const int ax, const int bx, const int cx, const int dx, const int var);
	string to_Marker(string word, List* list);
	string First_level();
	string Second_level();
	bool Varer();
	bool Marker(string word, List* List, data* what);
	bool Ending();
	const char* Files();
	bool Assembler();
	void Help();
	void End();


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
			if (Assembler())
			{
				End();
				return b;
			}
			else
			{
				printf("Error - ASM - Assembler\n");
				return false;
			}
		}
		else
		{
			return false;
		}
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
				End();
				return b;
			}
			else
			{
				printf("Error - ASM - Assembler\n");
				return false;
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
				return true;
			}
			else
			{
				fprintf(stderr, "ASM - Ending - False Label");
				return false;
			}
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
			}
			else
			{
				fprintf(stderr, "It's not a command. Start again\nYou can press exit or ignore this problem(if you are using the console)\n", word.c_str());
			}
			fprintf(stderr, "num:%d\n\n", num);
		}
	}
	if (Ending())
	{
		return true;
	}
	else
	{
		fprintf(stderr, "ASM - Ending - False Label");
		return false;
	}
}

string ASM::Commands(string word)
{
#define DUAL(STR, CONST) if(STR == word)\
		{ word = getStrFromNumber(CONST) ; num++; return word; }
	DUAL("add", ADD);
	DUAL("div", DIV);
	DUAL("sqrt", SQRT);
	DUAL("mul", MUL);
	DUAL("sub", SUB);
	DUAL("mov", MOV);
#undef DUAL

#define SINGLE(STR, CONST) if(STR == word)\
			{ word = getStrFromNumber(CONST) ; num++; return word; }
	SINGLE("halt", HALT);
	SINGLE("out", OUT);
	SINGLE("ded", DED);
	SINGLE("ret", RET);
	SINGLE("sin", SIN);
	SINGLE("cos", COS);
#undef SINGLE
	
#define COMP_F(STR, ax, bx, cx, dx, con, var) if(STR == word)\
				{ word = Complicate_F(ax, bx, cx, dx, con, var); if (word != "0") { num++; return word; } else return "0"; }
	COMP_F("push", PUSH_AX, PUSH_BX, PUSH_CX, PUSH_DX, PUSH_S, PUSH_V);
	COMP_F("pop", POP_AX, POP_BX, POP_CX, POP_DX, POP_S, POP_V);
	COMP_F("in", IN_AX, IN_BX, IN_CX, IN_DX, IN_S, IN_V);
	COMP_F("dec", DEC_AX, DEC_BX, DEC_CX, DEC_DX, DEC_S, DEC_V);
	COMP_F("inc", INC_AX, INC_BX, INC_CX, INC_DX, INC_S, INC_V);
#undef COMP_F

#define FUNC_JMP(STR) if (word == STR)\
				{ word = (to_Marker(word, head_)); if (word != "0") { return word; } else return "0"; }
	FUNC_JMP("ja");
	FUNC_JMP("jna");	
	FUNC_JMP("jb");
	FUNC_JMP("jnb");
	FUNC_JMP("je");
	FUNC_JMP("jne");
	FUNC_JMP("jmp");
	FUNC_JMP("calla");
	FUNC_JMP("callna");
	FUNC_JMP("callb");
	FUNC_JMP("callnb");
	FUNC_JMP("calle");
	FUNC_JMP("callne");
	FUNC_JMP("call");
	FUNC_JMP("func");
	FUNC_JMP("label");
#undef FUNC_JMP

	if (word == "var")
	{
		if (Varer())
		{
			num++;
			return (word = getStrFromNumber(VAR));
		}
	}
	return "0";
}

string ASM::Complicate_F(const int ax, const int bx, const int cx, const int dx, const int con, const int var)
{
	const int place = ftell(stdin);
	string this_word;
	std::cin >> this_word;
	fprintf(stderr, "Cin \"Complicate_F\" has read: %s\n", this_word.c_str());

	if ((con != INC_S) || (con != DEC_S) || (con != POP_S))
	{
		if (IsItNumber(this_word))
		{
			return(this_word = (getStrFromNumber(con) + " " + this_word));
		}
	}
	this_word = CommandsCPU(this_word, ax, bx, cx, dx, var);
	if (this_word != "0")
	{
		num--;
		return this_word;
	}
	if ((con == INC_S) || (con == DEC_S) || (con == POP_S))
	{
		fseek(stdin, place, SEEK_SET);
		return this_word = (getStrFromNumber(con));
	}
	else
	{
		fprintf(stderr, "But,...\n");
		return "0";
	}
}

string ASM::CommandsCPU(string word, const int ax, const int bx, const int cx, const int dx, const int var)
{
#define CHECK_CMD(STR, CONST) if(STR == word)\
		{ word = getStrFromNumber(CONST) ; num++; return word; }
	CHECK_CMD("cx", cx);
	CHECK_CMD("ax", ax);
	CHECK_CMD("dx", dx);
	CHECK_CMD("bx", bx);
#undef CHECK_CMD

	int x = Var_.IsItVariable(word);
	if (x != -1)
	{
		num++;
		return word = (getStrFromNumber(var) + " " + getStrFromNumber(x));
	}
	return "0";
}

bool ASM::Varer()
{
	string this_word;
	std::cin >> this_word;

	if (Var_.push_decl(this_word, num))
	{
		return true;
	}
	return false;
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

	if ((word == "func") || (word == "label"))
	{
		fprintf(stderr, "Cin \"Marker - declaration\" has read: %s\n", this_word.c_str());
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
	else if ((word == "call") || (word == "calla") || (word == "callna") || (word == "callb") ||\
		(word == "callnb") || (word == "calle") || (word == "callne") || (word == "jmp") || (word == "ja") ||\
		(word == "jnb") || (word == "jnb") || (word == "jne") || (word == "je") || (word == "jna"))
	{
		fprintf(stderr, "Cin \"Marker - action\" has read: %s\n", this_word.c_str());
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
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
		return false;
	}
}

bool ASM::Ending()
{
	size_t length = data_.size();
	for (size_t i = 0; i < length; i++)
	{
		List* tmp1 = data_.lists_jx(i);
		if (tmp1)
		{
			int a = data_.numbers_jx(i);
			if (a != -1)
			{
				tmp1->write(getStrFromNumber(a));
			}
			else
			{
				fprintf(stderr, "Error - Ending - wrong label\n");
				return false;
			}
		}
		else
		{
			fprintf(stderr, "Error - Ending - wrong label\n");
			return false;
		}
	}
	length = Func_.size();
	for (size_t i = 0; i < length; i++)
	{
		List* tmp1 = Func_.lists_jx(i);
		if (tmp1)
		{
			int a = Func_.numbers_jx(i);
			if (a != -1)
			{
				tmp1->write(getStrFromNumber(a));
			}
			else
			{
				fprintf(stderr, "Error - Ending - wrong label\n");
				return false;
			}
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