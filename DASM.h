#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "Enum.h"
#include "List.h"
#include "Pointer.h"

using std::string;

class DASM
{
private:
	List* data_;
	FILE* file;
	size_t num;
	Pointer Pointer_;

	bool File(const char* output);
	bool Reader(string word);
	string Commands(string word);
	string Dual_DASM(int level);
	string level_(char X, int level);
	string Slevel_(string com, int level);
	string return_reg(string word);
	string Check_Dual_DASM(string Dual, string word, char* str);
	bool Pointer(string word);
	bool Ending();
	string Check_Var(string word, char* comm);

public:
	int Dialog(const char* output);

	explicit DASM() :
		num(0) { data_ = nullptr; }

};

int DASM::Dialog(const char* output)
{
	//printf("Do you what to disassemble the code?\n(yes)/(no)\n");
	while (true)
	{
		char request[MAX_CMD_SIZE] = "yes";
		//scanf("%s", &request);
		if (strcmp("yes", request) == 0)
		{
			if (File(output))
			{
				if (Reader("true"))
				{
					printf("\nDisassembling...\n ");
					data_->print();
					fclose(file);
					return 1;
				}
				else
				{
					fclose(file);
					return 0;
				}
			}
			else
			{
				fclose(file);
				return 0;
			}
		}
		if (strcmp("no", request) == 0)
		{
			return -1;
		}
		printf("It's not a command. Try again.\n");
	}
}

bool DASM::File(const char* output)
{
	file = fopen(output, "w");
	if (file)
	{
		Pointer_.push_file(file);
		return true;
	}
	else
	{
		fprintf(stderr, "  err %s \n", strerror(errno));
		printf("Error - File\n");
		return false;
	}
}

bool DASM::Reader(string word)
{	
	data_ = (data_) ? data_->push() : new List();
	word = Commands(word);
	if (word == "0")
	{
		printf("Error - Reader\n");
		return false;
	}
	if (word == "stop")
	{
		if (Ending())
		{
			return true;
		}
		else return false;
	}
	else
	{
		data_->pusher(word);
		num++;
		Reader(word);
	}
}

string DASM::Commands(string word)
{
	while (!feof(file))
	{
		char buf[MAX_CMD_SIZE];
		fscanf(file, "%s", &buf);
		word = buf;
		printf("Commands read: %s\n", word.c_str());
#define CHECK_Z_D(CONST, STR) if(word == gtf(CONST)) { return STR; }
		CHECK_Z_D(RET, "ret\n\n");
		CHECK_Z_D(DED, "ded\n");
		CHECK_Z_D(HALT, "halt\n");
		CHECK_Z_D(OUT, "out\n");
		CHECK_Z_D(ADD_S, "add\n");
		CHECK_Z_D(MUL_S, "mul\n");
		CHECK_Z_D(DIV_S, "div\n");
		CHECK_Z_D(SUB_S, "sub\n");
#undef CHECK_Z_D
#define CHECK_P_D(CONST) if(word == gtf(CONST))\
			{ word = Pointer_.push_point(word, num); if(word != "0") { return word; } else return "0"; }
		CHECK_P_D(LABEL);
		CHECK_P_D(FUNC);
#undef CHECK_P_D
#define CHECK_S_D(CONST, STR) if(word == gtf(CONST)) { return STR; }
		CHECK_S_D(PUSH_AX, "push ax\n");	CHECK_S_D(PUSH_BX, "push bx\n");	CHECK_S_D(PUSH_CX, "push cx\n");
		CHECK_S_D(PUSH_DX, "push dx\n");	CHECK_S_D(SQRT_S, "sqrt\n");		CHECK_S_D(SQRT_AX, "sqrt ax\n");
		CHECK_S_D(SQRT_BX, "sqrt bx\n");	CHECK_S_D(SQRT_CX, "sqrt cx\n");	CHECK_S_D(SQRT_DX, "sqrt dx\n");
		CHECK_S_D(POP_S, "pop\n");			CHECK_S_D(POP_AX, "pop ax\n");		CHECK_S_D(POP_BX, "pop bx\n");
		CHECK_S_D(POP_CX, "pop cx\n");		CHECK_S_D(POP_DX, "pop dx\n");		CHECK_S_D(INC_S, "inc\n");
		CHECK_S_D(INC_AX, "inc ax\n");		CHECK_S_D(INC_BX, "inc bx\n");		CHECK_S_D(INC_CX, "inc cx\n");
		CHECK_S_D(INC_DX, "inc dx\n");		CHECK_S_D(DEC_S, "dec\n");			CHECK_S_D(DEC_AX, "dec ax\n");
		CHECK_S_D(DEC_BX, "dec bx\n");		CHECK_S_D(DEC_CX, "dec cx\n");		CHECK_S_D(DEC_DX, "dec dx\n");
		CHECK_S_D(IN_S, "in\n");			CHECK_S_D(IN_AX, "in ax\n");		CHECK_S_D(IN_BX, "in bx\n");
		CHECK_S_D(IN_CX, "in cx\n");		CHECK_S_D(IN_DX, "in dx\n");
#undef CHECK_S_D
#define CHECK_J_D(CONST, STR) if(word == gtf(CONST))\
					{ if(Pointer_.push_do(STR, data_)) { return STR; } else return "0"; }
		CHECK_J_D(JMP, "jmp ");
		CHECK_J_D(J_A, "ja ");
		CHECK_J_D(J_NA, "jna ");
		CHECK_J_D(J_B, "jb ");
		CHECK_J_D(J_NB, "jnb ");
		CHECK_J_D(J_E, "je ");
		CHECK_J_D(J_NE, "jne ");
		CHECK_J_D(CALL, "call ");
		CHECK_J_D(CALL_A, "calla ");
		CHECK_J_D(CALL_NA, "callna ");
		CHECK_J_D(CALL_B, "callb ");
		CHECK_J_D(CALL_NB, "callnb ");
		CHECK_J_D(CALL_E, "calle ");
		CHECK_J_D(CALL_NE, "callne ");
#undef CHECK_J_D
#define CHECK_DUAL(CONST, STR) if (word == gtf(CONST))\
			{ word = Check_Dual_DASM(Dual_DASM(0), word, STR); if(word != "0") return word; else return "0"; }
		CHECK_DUAL(ADD_D, "add ");
		CHECK_DUAL(DIV_D, "div ");
		CHECK_DUAL(MUL_D,  "mul ");
		CHECK_DUAL(SUB_D, "sub ");
		CHECK_DUAL(MOV_D, "mov ");
#undef CHECK_DUAL
#define CHECK_VAR_D(CONST, STR) if (word == gtf(CONST)) { word = Check_Var(word, STR); if (word != "0")\
				{ return word; } else return "0"; }
		CHECK_VAR_D(PUSH_V, "push ");
		CHECK_VAR_D(POP_V, "pop ");
		CHECK_VAR_D(SQRT_V, "sqrt ");
		CHECK_VAR_D(INC_V, "inc ");
		CHECK_VAR_D(DEC_V, "dec ");
		CHECK_VAR_D(IN_V, "in ");
#undef CHECK_VAR_D

		if (word == gtf(VAR))
		{
			word = Pointer_.push_var(num);
			if ( word == "0" )
			{
				printf("Error - pointer\n");
				return "0";
			}
			else return word;
		}
		if (word == gtf(PUSH_S))
		{
			word = "push ";
			string that_word;
			fscanf(file, "%s", &buf);
			that_word = buf;
			if (IsItNumber(that_word))
			{
				return word + " " + that_word + "\n";
			}
			else
			{
				printf("Error - push s\n");
				return "0";
			}
		}
		printf("Error - Commands\n");
		return "0";
	}
	return "stop";
}

string DASM::Check_Dual_DASM(string dual, string word, char* str)
{
	word = str;
	if (dual != "0")
	{
		word = word + dual;
		return word;
	}
	else
	{
		printf("Error - Check Dual\n");
		return false;
	}
}

string DASM::Check_Var(string word, char* comm)
{
	string that_word;
	int buf;
	fscanf(file, "%d", &buf);
	if (buf == VAR_D)
	{
		fscanf(file, "%d", &buf);
		that_word = Pointer_.return_var(buf - 1);
		if (that_word != "0")
		{
			word = comm;
			return word + that_word + "\n";
		}
		else
		{
			printf("Error - return var\n");
			return "0";
		}
	}
	printf("Error - VAR_D\n");
	return "0";
}

string DASM::Dual_DASM(int level)
{
	string word;
	char word_this[MAX_CMD_SIZE];
	fscanf(file, "%s", word_this);
	printf("Dual_DASM has read:%s\n", word_this);
	if ((word_this[0] == 'V') && (word_this[1] == '\0'))
	{
		word = level_('V', level);
		if (word == "0")
		{
			printf("Error - level - back\n");
			return "0";
		}
		else return word;
	}
	if ((word_this[0] == 'R') && (word_this[1] == '\0'))
	{
		word = level_('R', level);
		if (word == "0")
		{
			printf("Error - level - back\n");
			return "0";
		}
		else return word;
	}
	if ((word_this[0] == 'N') && (word_this[1] == '\0') && (1 < level < 2))
	{
		word = level_('N', level);
		if (word == "0")
		{
			printf("Error - level - back\n");
			return "0";
		}
		else return word;
	}
	else
	{
		printf("Error - dual - level %d\n", level);
		return "0";
	}
}

string DASM::level_(char X, int level)
{
	string com;
	int buf;
	fscanf(file, "%d", &buf);
	if ((level < 2) && (X == 'V'))
	{
		com = Pointer_.return_var(buf - 1);
		com = Slevel_(com, level);
		if (com != "0")
		{
			return com;
		}
		else return "0";
	}
	if ((0 < level < 2) && (X == 'N'))
	{
		com = gtf(buf);
		if (com != "0")
		{
			return com;
		}
		else
		{
			printf("Error - num\n");
			return "0";
		}
	}
	if ((level < 2) && (X == 'R'))
	{
		com = gtf(buf);
		com = return_reg(com);
		com = Slevel_(com, level);
		if (com != "0")
		{
			return com;
		}
		else return "0";
	}
	else
	{
		return "0";
	}
}

string DASM::Slevel_(string com, int level)
{
	if (com != "0")
	{
		if (level == 0)
		{
			string that_com = Dual_DASM(1);
			if (that_com != "0")
			{
				com = com + "\, " + that_com + "\n";
			}
			else
			{
				printf("Error - level 1\n");
				return "0";
			}
		}
		return com;
	}
	else
	{
		printf("Error - Slevel_\n");
		return "0";
	}
}

string DASM::return_reg(string word)
{
#define REG(NUM, STR) if(word == gtf(NUM)) { word = STR; return word; }
	REG(AX, "ax");	REG(BX, "bx");
	REG(DX, "dx");	REG(CX, "cx");
#undef REG
	printf("Error - return_reg\n");
	return "0";
}

bool DASM::Ending()
{
	size_t length = Pointer_.size();
	for (size_t i = 0; i < length; i++)
	{
		List* tmp1 = Pointer_.lists_(i);
		if (tmp1)
		{
			string a = Pointer_.names_(i);
			if (a != "0")
			{
				tmp1->write(a);
			}
			else
			{
				fprintf(stderr, "Error - Ending - wrong name!!!\n");
				return false;
			}
		}
		else
		{
			fprintf(stderr, "Error - Ending - wrong list\n");
			return false;
		}
	}
	return true;
}