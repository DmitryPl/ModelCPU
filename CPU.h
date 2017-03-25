#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "math.h"
#include "iostream"
#include "Stack.h"
#include "Enum.h"
#include "Functions.h"

class CPU
{
private:
	Stack Stack_CPU;
	Stack of_Function;
	Functions Mrakobesie;
	int ax, bx, cx, dx;
	size_t num;
	FILE *file;

	bool Files(const char* output);
	bool Reader();
	void Excerpt();
	MyFuncType* Commands(int word);
	void Arrayer();
	void print();

	bool ADD_F(int);
	bool SIN_F(int);
	bool COS_F(int);
	bool DEC_F(int);
	bool INC_F(int);
	bool DED_F(int);
	bool DIV_F(int);
	bool SUB_F(int);
	bool SUM_F(int);
	bool SQRT_F(int);
	bool HMD_F(int);
	bool OUT_F(int);
	bool PUSH_AX_F(int);
	bool PUSH_BX_F(int);
	bool PUSH_CX_F(int);
	bool PUSH_DX_F(int);
	bool IN_AX_F(int);
	bool IN_BX_F(int);
	bool IN_CX_F(int);
	bool IN_DX_F(int);
	bool POP_AX_F(int);
	bool POP_BX_F(int);
	bool POP_CX_F(int);
	bool POP_DX_F(int);
	bool LABEL_F(int);
	bool FUNC_F(int);
	bool RET_F(int);

	bool PUSH_F(int x);
	bool JA_F(int x);
	bool JC_F(int x);
	bool JP_F(int x);
	bool JMP_F(int x);
	bool CALLA_F(int x);
	bool CALLC_F(int x);
	bool CALLP_F(int x);

public:
	explicit CPU() :
		ax(0), bx(0), cx(0), dx(0), num(0)
	{ 
		Mrakobesie = {};
	}

	bool CPU_(const char* output);

};

bool CPU::CPU_(const char* output)
{
	fprintf(stderr, "\nSTARTING CPU\n");
	if (Files(output))
	{
		doNothing();
	}
	if (Reader())
	{
		fclose(file);
		fprintf(stderr, "\nEND CPU\n");
		return true;
	}
	else return false;
}

bool CPU::Files(const char* output)
{
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);
	file = fopen(output, "r");
	if (file)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CPU::Reader()
{
	while (!feof(file))
	{
		int word = 0;
		MyFuncType* i = nullptr;
		fscanf(file, "%d", &word);
		printf("Scanf \"Reader\" has read: %d\n", word);
		i = Commands(word);
		if (i != nullptr)
		{
			Mrakobesie.push(*i);
			num++;
		}
		else
		{
			printf("It's not a command! %d\n", word);
			return false;
		}
	}
	Excerpt();
	return true;
}

void CPU::Excerpt()
{
	printf("\nSTART...\n");
	getch();
	num = 0;
	int b;
	while (num < Mrakobesie.size_type())
	{
		b = Mrakobesie.return_numbers(num);
		(this->*Mrakobesie.do_(num))(b);
		num++;
	}
}

MyFuncType* CPU::Commands(int word)
{
	CHECK_CPU(word, ADD, ADD_F);
	CHECK_CPU(word, SIN, SIN_F);
	CHECK_CPU(word, COS, COS_F);
	CHECK_CPU(word, DIV, DIV_F);
	CHECK_CPU(word, SQRT, SQRT_F);
	CHECK_CPU(word, SUM, SUM_F);
	CHECK_CPU(word, SUB, SUB_F);
	CHECK_CPU(word, HMD, HMD_F);
	CHECK_CPU(word, DED, DED_F);
	CHECK_CPU(word, INC, INC_F);
	CHECK_CPU(word, DEC, DEC_F);
	CHECK_CPU(word, OUT, OUT_F);
	CHECK_CPU(word, PUSH_AX, PUSH_AX_F);
	CHECK_CPU(word, PUSH_BX, PUSH_BX_F);
	CHECK_CPU(word, PUSH_CX, PUSH_CX_F);
	CHECK_CPU(word, PUSH_DX, PUSH_DX_F);
	CHECK_CPU(word, PUSH_AX, IN_AX_F);
	CHECK_CPU(word, PUSH_BX, IN_BX_F);
	CHECK_CPU(word, PUSH_CX, IN_CX_F);
	CHECK_CPU(word, PUSH_DX, IN_DX_F);
	CHECK_CPU(word, POP_AX, POP_AX_F);
	CHECK_CPU(word, POP_DX, POP_DX_F);
	CHECK_CPU(word, POP_CX, POP_CX_F);
	CHECK_CPU(word, POP_BX, POP_BX_F);
	CHECK_CPU(word, IN_AX, IN_AX_F);
	CHECK_CPU(word, IN_DX, IN_DX_F);
	CHECK_CPU(word, IN_CX, IN_CX_F);
	CHECK_CPU(word, IN_BX, IN_BX_F);
	CHECK_CPU(word, LABEL, LABEL_F);
	CHECK_CPU(word, FUNC, FUNC_F);
	CHECK_CPU(word, RET, RET_F);

	CHECK_CPU_F(word, PUSH, PUSH_F);
	CHECK_CPU_F(word, JC, JC_F);
	CHECK_CPU_F(word, JA, JA_F);
	CHECK_CPU_F(word, JMP, JMP_F);
	CHECK_CPU_F(word, JP, JP_F);
	CHECK_CPU_F(word, CALLA, CALLA_F);
	CHECK_CPU_F(word, CALLC, CALLC_F);
	CHECK_CPU_F(word, CALLP, CALLP_F);
	return nullptr;
}

void CPU::Arrayer()
{
	int zzz;
	fscanf(file, "%d", &zzz);
	printf("Scanf \"Arrayer\" has read: %d \n", zzz);
	Mrakobesie.write_numbers(num, zzz);
}

void CPU::print()
{
	printf("***************\n");
	printf("STACK CPU: ");
	Stack_CPU.print();
	printf("\n");
	printf("AX: %d, BX: %d, CX: %d, DX: %d\n", ax, bx, cx, dx);
	printf("***************\n");
}

bool CPU::ADD_F(int)
{
	if (Stack_CPU.size() > 2)
	{
		int tmp1 = Stack_CPU.pop();
		int tmp2 = Stack_CPU.pop();
		Stack_CPU.push(tmp1 + tmp2);
		print();
		return true;
	}
	else
	{
		printf("Error - Stack has't not got 2 numbers - DIV\n");
		print();
		return false;
	}
}
bool CPU::SIN_F(int)
{
	printf("sin ax / 360 = %f!\n", sin(ax / 360));
	return true;
}
bool CPU::COS_F(int)
{
	printf("cos ax / 360 = %f!\n", cos(ax / 360));
	return true;
}
bool CPU::DEC_F(int)
{
	dx--;
	print();
	return true;
}
bool CPU::INC_F(int)
{
	dx++;
	print();
	return true;
}
bool CPU::DED_F(int)
{
	printf("\nDo you respect the SPACE?\n\n");
	return true;
}
bool CPU::DIV_F(int)
{
	if (Stack_CPU.size() > 2)
	{
		int tmp1 = Stack_CPU.pop();
		int tmp2 = Stack_CPU.pop();
		Stack_CPU.push(tmp1 / tmp2);
		print();
		return true;
	}
	else
	{
		printf("Error - Stack has't not got 2 numbers - DIV\n");
		print();
		return false;
	}
}
bool CPU::SUB_F(int)
{
	if (Stack_CPU.size() > 2)
	{
		int tmp1 = Stack_CPU.pop();
		int tmp2 = Stack_CPU.pop();
		Stack_CPU.push(tmp1 - tmp2);
		print();
		return true;
	}
	else
	{
		printf("Error - Stack has't not got 2 numbers - DIV\n");
		print();
		return false;
	}
}
bool CPU::SUM_F(int)
{
	if (Stack_CPU.size() > 2)
	{
		int tmp1 = Stack_CPU.pop();
		int tmp2 = Stack_CPU.pop();
		Stack_CPU.push(tmp1 * tmp2);
		print();
		return true;
	}
	else
	{
		printf("Error - Stack has't not got 2 numbers - DIV\n");
		print();
		return false;
	}
}
bool CPU::SQRT_F(int)
{
	if (!Stack_CPU.empty())
	{
		Stack_CPU.push(sqrt(Stack_CPU.pop()));
		print();
		return true;
	}
	else
	{
		printf("Error - sqrt - empty\n");
		print();
		return false;
	}
}
bool CPU::HMD_F(int)
{
	num = Mrakobesie.size_type();
	return true;
}
bool CPU::OUT_F(int)
{
	printf("***************\n");
	printf("STACK CPU: ");
	Stack_CPU.print();
	printf("\n");
	printf("AX: %d, BX: %d, CX: %d, DX: %d\n", ax, bx, cx, dx);
	printf("***************\n");
	return true;
}
bool CPU::PUSH_AX_F(int)
{
	Stack_CPU.push(ax);
	print();
	return true;
}
bool CPU::PUSH_BX_F(int)
{
	Stack_CPU.push(bx);
	print();
	return true;
}
bool CPU::PUSH_CX_F(int)
{
	Stack_CPU.push(cx);
	print();
	return true;
}
bool CPU::PUSH_DX_F(int)
{
	Stack_CPU.push(cx);
	print();
	return true;
}
bool CPU::IN_AX_F(int)
{
	while (true)
	{
		printf("ENTER NUMBER (AX):\n");
		string this_word;
		std::cin >> this_word;
		if (IsItNumber(this_word))
		{
			ax = atoi(this_word.c_str());
			print();
			return true;
		}
		else
		{
			printf("It's not a number, try again.\n");
		}
	}
}
bool CPU::IN_BX_F(int)
{
	while (true)
	{
		printf("ENTER NUMBER (AX):\n");
		string this_word;
		std::cin >> this_word;
		if (IsItNumber(this_word))
		{
			bx = atoi(this_word.c_str());
			print();
			return true;
		}
		else
		{
			printf("It's not a number, try again.\n");
		}
	}
}
bool CPU::IN_CX_F(int)
{
	while (true)
	{
		printf("ENTER NUMBER (AX):\n");
		string this_word;
		std::cin >> this_word;
		if (IsItNumber(this_word))
		{
			cx = atoi(this_word.c_str());
			print();
			return true;
		}
		else
		{
			printf("It's not a number, try again.\n");
		}
	}
}
bool CPU::IN_DX_F(int)
{
	while (true)
	{
		printf("ENTER NUMBER (AX):\n");
		string this_word;
		std::cin >> this_word;
		if (IsItNumber(this_word))
		{
			dx = atoi(this_word.c_str());
			print();
			return true;
		}
		else
		{
			printf("It's not a number, try again.\n");
		}
	}
}
bool CPU::POP_AX_F(int)
{
	if (!Stack_CPU.empty())
	{
		ax = Stack_CPU.pop();
		print();
		return true;
	}
	else
	{
		printf("Stack - empty - error!\n");
		print();
		return false;
	}
}
bool CPU::POP_BX_F(int)
{
	if (!Stack_CPU.empty())
	{
		bx = Stack_CPU.pop();
		print();
		return true;
	}
	else
	{
		printf("Stack - empty - error!\n");
		print();
		return false;
	}
}
bool CPU::POP_CX_F(int)
{
	if (!Stack_CPU.empty())
	{
		cx = Stack_CPU.pop();
		print();
		return true;
	}
	else
	{
		printf("Stack - empty - error!\n");
		print();
		return false;
	}
}
bool CPU::POP_DX_F(int)
{
	if (!Stack_CPU.empty())
	{
		dx = Stack_CPU.pop();
		print();
		return true;
	}
	else
	{
		printf("Stack - empty - error!\n");
		print();
		return false;
	}
}
bool CPU::LABEL_F(int)
{
	return true;
}
bool CPU::FUNC_F(int)
{
	return true;
}
bool CPU::RET_F(int)
{
	if (!of_Function.empty())
	{
		num = of_Function.pop();
		return true;
	}
	else
	{
		num = Mrakobesie.size_type();
	}
}

bool CPU::PUSH_F(int x)
{
	if (x != NAN)
	{
		Stack_CPU.push(x);
		print();
		return true;
	}
	else
	{
		printf("Error - PUSH_F\n");
		print();
		return false;
	}
}
bool CPU::JA_F(int x)
{
	if (x != NAN)
	{
		if (Stack_CPU.size() > 2)
		{
			int tmp1 = Stack_CPU.pop();
			int tmp2 = Stack_CPU.pop();
			if (tmp1 >= tmp2)
			{
				num = x - 1;
			}
			Stack_CPU.push(tmp2);
			Stack_CPU.push(tmp1);
			return true;
		}
		else
		{
			printf("Error - JA_F - empty\n");
			print();
			return false;
		}
	}
	else
	{
		printf("Error - JA_F\n");
		print();
		return false;
	}
}
bool CPU::JC_F(int x)
{
	if (x != NAN)
	{
		if (Stack_CPU.size() > 2)
		{
			int tmp1 = Stack_CPU.pop();
			int tmp2 = Stack_CPU.pop();
			if (tmp1 == tmp2)
			{
				num = x - 1;
			}
			Stack_CPU.push(tmp2);
			Stack_CPU.push(tmp1);
			return true;
		}
		else
		{
			printf("\nError - JC_F - empty\n");
			print();
			return false;
		}
	}
	else
	{
		printf("Error - JC_F\n");
		print();
		return false;
	}
}
bool CPU::JP_F(int x)
{
	if (x != NAN)
	{
		if (Stack_CPU.size() > 2)
		{
			int tmp1 = Stack_CPU.pop();
			int tmp2 = Stack_CPU.pop();
			if (tmp1 <= tmp2)
			{
				num = x - 1;
			}
			Stack_CPU.push(tmp2);
			Stack_CPU.push(tmp1);
			return true;
		}
		else
		{
			print();
			printf("\nError - JP_F - empty\n");
			return false;
		}
	}
	else
	{
		print();
		printf("Error - JP_F\n");
		return false;
	}
}
bool CPU::JMP_F(int x)
{
	if (x != NAN)
	{
		num = x - 1;
		return true;
	}
	else
	{
		printf("Error - JMP_F\n");
		print();
		return false;
	}
}
bool CPU::CALLA_F(int x)
{
	if (x != NAN)
	{
		of_Function.push(num);
		num = x;
		return true;
	}
	else
	{
		printf("Error - CALLA_F\n");
		print();
		return false;
	}
}
bool CPU::CALLC_F(int x)
{
	if (x != NAN)
	{
		of_Function.push(num);
		num = x;
		return true;
	}
	else
	{
		printf("Error - CALLC_F\n");
		print();
		return false;
	}
}
bool CPU::CALLP_F(int x)
{
	if (x != NAN)
	{
		of_Function.push(num);
		num = x;
		return true;
	}
	else
	{
		printf("Error - CALLP_F\n");
		print();
		return false;
	}
}
