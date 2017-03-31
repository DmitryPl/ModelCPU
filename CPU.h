#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "math.h"
#include "map"
#include "iostream"
#include "Stack.h"
#include "Enum.h"
#include "Functions.h"
#include "SingleType.h"

using std::map;
typedef map<size_t, int> Variable_T;
typedef bool(*CompFunction)(int, int);

class CPU
{
private:
	Stack Stack_CPU;
	Stack of_Function;
	Functions Mrakobesie;
	SingleType China;
	Variable_T Variable_;
	int ax, bx, cx, dx;
	size_t num;
	FILE *file;

	bool Files(const char* output);
	bool Reader();
	bool Excerpt();
	MyFuncType Commands(int word);
	void Jumper_CPU(int word);
	void Call_Jmp(int word);
	bool conditionJump(CompFunction comp, string nameOfOperation);
	bool VAR_();
	bool Single_CPU(int word);
	void Dual_CPU(int word);
	void print() const;
	void print_var() const;
	int* Choose_Reg(const int x);
	bool doNothing_vr2();

	bool ADD_();
	bool DEC_();
	bool INC_();
	bool DED_();
	bool DIV_();
	bool SUB_();
	bool MUL_();
	bool SQRT_();
	bool HALT_();
	bool OUT_();
	bool IN_();
	bool POP_();
	bool RET_();
	bool PUSH_();
	bool JMP_();
	bool CALL_();
	bool MOV_D_();
	bool DIV_D_();
	bool SUB_D_();
	bool MUL_D_();
	bool ADD_D_();
	bool J_A_L();
	bool J_NA_L();
	bool J_NB_L();
	bool J_B_L();
	bool J_E_L();
	bool J_NE_L();
	bool JMP_L();
	bool CALL_A_F();
	bool CALL_NA_F();
	bool CALL_B_F();
	bool CALL_NB_F();
	bool CALL_E_F();
	bool CALL_NE_F();
	bool CALL_F();

public:
	explicit CPU() :
		ax(0), bx(0), cx(0), dx(0), num(0)
	{ 	}

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
		MyFuncType i = nullptr;
		fscanf(file, "%d", &word);
		printf("Scanf \"Reader\" has read: %d\n", word);
		i = Commands(word);
		if (i != nullptr)
		{
			Mrakobesie.push(i);
			num++;
		}
		else
		{
			printf("It's not a command! %d\n", word);
			return false;
		}
	}
	if (!Excerpt())
	{
		return false;
	}
	return true;
}

bool CPU::VAR_()
{
	int x = 0;
	Variable_.insert(std::pair<size_t, int>(num + 1, x));
	return true;
}

bool CPU::Excerpt()
{
	Mrakobesie.print();
	China.print();
	printf("\nSTART...\n");
	getch();
	num = 0;
	while (num < Mrakobesie.size_type())
	{
		if ((this->*Mrakobesie.do_(num))())
		{
			printf("num: \n%d\n", num);
			num++;
		}
		else
		{
			printf("Error - Excerpt");
			return false;
		}
	}
	return true;
}

MyFuncType CPU::Commands(int word)
{
#define CHECK_ZERO(CONST, POINTER) if(word == CONST)\
		{ MyFuncType res = &CPU::POINTER; return res; }
	CHECK_ZERO(RET, RET_);
	CHECK_ZERO(DED, DED_);
	CHECK_ZERO(HALT, HALT_);
	CHECK_ZERO(OUT, OUT_);
	CHECK_ZERO(ADD_S, ADD_);
	CHECK_ZERO(MUL_S, MUL_);
	CHECK_ZERO(DIV_S, DIV_);
	CHECK_ZERO(SUB_S, SUB_);
	CHECK_ZERO(LABEL, doNothing_vr2);
	CHECK_ZERO(FUNC, doNothing_vr2);
#undef CHECK_ZERO

#define CHECK_SINGLE(con, ax, bx, cx, dx, var, POINTER)\
	if((word == con) || (word ==  ax) || (word == bx) || (word == cx) || (word == dx) || (word == var))\
						{ if(Single_CPU(word)){ MyFuncType res = &CPU::POINTER; return res; } else return nullptr; }
	CHECK_SINGLE(PUSH_S, PUSH_AX, PUSH_BX, PUSH_CX, PUSH_DX, PUSH_V, PUSH_);
	CHECK_SINGLE(SQRT_S, SQRT_AX, SQRT_BX, SQRT_CX, SQRT_DX, SQRT_V, SQRT_);
	CHECK_SINGLE(POP_S, POP_AX, POP_BX, POP_CX, POP_DX, NULL, POP_);
	CHECK_SINGLE(INC_S, INC_AX, INC_BX, INC_CX, INC_DX, INC_V, INC_);
	CHECK_SINGLE(DEC_S, DEC_AX, DEC_BX, DEC_CX, DEC_DX, DEC_V, DEC_);
	CHECK_SINGLE(IN_S, IN_AX, IN_BX, IN_CX, IN_DX, IN_V, IN_);
#undef CHECK_SINGLE

#define CHECK_JMP(CONST, POINTER) if(word == CONST)\
				{ Call_Jmp(word); MyFuncType res = &CPU::POINTER; return res; }
	CHECK_JMP(JMP, JMP_L);
	CHECK_JMP(J_A, J_A_L);
	CHECK_JMP(J_NA, J_NA_L);
	CHECK_JMP(J_B, J_NA_L);
	CHECK_JMP(J_NB, J_NB_L);
	CHECK_JMP(J_E, J_E_L);
	CHECK_JMP(J_NE, J_NE_L);
#undef CHECK_JMP

#define CHECK_CALL(CONST, POINTER) if(word == CONST)\
				{ Call_Jmp(word); MyFuncType res = &CPU::POINTER; return res; }
	CHECK_CALL(CALL, CALL_F);
	CHECK_CALL(CALL_A, CALL_A_F);
	CHECK_CALL(CALL_NA, CALL_NA_F);
	CHECK_CALL(CALL_B, CALL_B_F);
	CHECK_CALL(CALL_NB, CALL_NB_F);
	CHECK_CALL(CALL_E, CALL_E_F);
	CHECK_CALL(CALL_NE, CALL_NE_F);
#undef CHECK_CALL

#define CHECK_DUAL(CONST, POINTER) if (word == CONST)\
				{ Dual_CPU(word); MyFuncType res = &CPU::POINTER; return res; }
	CHECK_DUAL(ADD_D, ADD_D_);
	CHECK_DUAL(DIV_D, DIV_D_);
	CHECK_DUAL(MUL_D, MUL_D_);
	CHECK_DUAL(SUB_D, SUB_D_);
	CHECK_DUAL(MOV_D, MOV_D_);
#undef CHECK_DUAL
	if (word == VAR)
	{
		VAR_();
		return &CPU::doNothing_vr2;
	}

	return nullptr;
}

bool CPU::Single_CPU(int word)
{
	if ((word == INC_S) || (word == DEC_S) || (word == SQRT_S) || (word == POP_S) || (word == IN_S))
	{
		China.push(num, NULL, word);
		return true;
	}
	if ((word == INC_AX) || (word == DEC_AX) || (word == PUSH_AX) || (word == SQRT_AX) || (word == POP_AX) || (word == IN_AX))
	{
		China.push(num, NULL, word);
		return true;
	}
	if ((word == INC_BX) || (word == DEC_BX) || (word == PUSH_BX) || (word == SQRT_BX) || (word == POP_BX) || (word == IN_BX))
	{
		China.push(num, NULL, word);
		return true;
	}
	if ((word == INC_CX) || (word == DEC_CX) || (word == PUSH_CX) || (word == SQRT_CX) || (word == POP_CX) || (word == IN_CX))
	{
		China.push(num, NULL, word);
		return true;
	}
	if ((word == INC_DX) || (word == DEC_DX) || (word == PUSH_DX) || (word == SQRT_DX) || (word == POP_DX) || (word == IN_DX))
	{
		China.push(num, NULL, word);
		return true;
	}
	int num_this;
	fscanf(file, "%d", &num_this);
	if ((word == INC_V) || (word == DEC_V) || (word == PUSH_V) || (word == SQRT_V) || (word == IN_V))
	{
		printf("Scanf \"Single\" has read: %d\n", num_this);
		if (num_this == VAR_D)
		{
			fscanf(file, "%d", &num_this);
			China.push(num, num_this, word);
			return true;
		}
		else
		{
			printf("Error - var - enter\n");
			return false;
		}
	}
	if (word == PUSH_S)
	{
		printf("Scanf \"Single\" has read: %d\n", num_this);
		China.push(num, num_this, word);
		return true;
	}
	printf("Error - Single Func\n");
	return false;
}

void CPU::Dual_CPU(int word)
{

}

void CPU::Call_Jmp(int word)
{
	int n;
	fscanf(file, "%d", &n);
	printf("Scanf \"Caller\" has read: %d \n", n);
	Mrakobesie.write_numbers(num, n);
}

void CPU::print() const
{
	printf("***************\n");
	printf("STACK CPU: ");
	Stack_CPU.print();
	print_var();
	printf("\n");
	printf("STACK FUNC: ");
	of_Function.print();
	printf("AX: %d, BX: %d, CX: %d, DX: %d NUM: %d\n", ax, bx, cx, dx, num);
	printf("***************\n");
}

void CPU::print_var() const
{
	std::cout << "Variable contains:\n";
	for (auto it = Variable_.begin(); it != Variable_.end(); ++it)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

bool CPU::doNothing_vr2()
{
	return true;
}

bool CPU::ADD_()
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
bool CPU::DIV_()
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
bool CPU::SUB_()
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
bool CPU::MUL_()
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
bool CPU::DED_()
{
	printf("\nDo you respect the SPACE?\n\n");
	return true;
}
bool CPU::HALT_()
{
	num = Mrakobesie.size_type();
	return true;
}
bool CPU::OUT_()
{
	printf("***************\n");
	printf("STACK CPU: ");
	Stack_CPU.print();
	printf("\n");
	printf("Variable:\n");
	print_var();
	printf("\n");
	printf("AX: %d, BX: %d, CX: %d, DX: %d\n", ax, bx, cx, dx);
	printf("***************\n");
	return true;
}
bool CPU::RET_()
{
	if (!of_Function.empty())
	{
		num = of_Function.pop();
		return true;
	}
	else
	{
		return false;
	}
}

bool CPU::MOV_D_()
{
	return true;
}
bool CPU::DIV_D_()
{
	return true;
}
bool CPU::SUB_D_()
{
	return true;
}
bool CPU::MUL_D_()
{
	return true;
}
bool CPU::ADD_D_()
{
	return true;
}

int* CPU::Choose_Reg(const int x)
{
	if ((x == IN_AX) || (x == PUSH_AX) || (x == SQRT_AX) || (x == POP_AX) || (x == INC_AX) || (x == DEC_AX))
	{
		if (x == IN_AX)
		{
			printf("ENTER NUMBER (AX):\n");
		}
		return &ax;
	}
	if ((x == IN_BX) || (x == PUSH_BX) || (x == SQRT_BX) || (x == POP_BX) || (x == INC_BX) || (x == DEC_BX))
	{
		if (x == IN_BX)
		{
			printf("ENTER NUMBER (BX):\n");
		}
		return &bx;
	}
	if ((x == IN_CX) || (x == PUSH_CX) || (x == SQRT_CX) || (x == POP_CX) || (x == INC_CX) || (x == DEC_CX))
	{	
		if (x == IN_CX)
		{
			printf("ENTER NUMBER (CX):\n");
		}
		return &cx;
	}
	if ((x == IN_DX) || (x == PUSH_DX) || (x == SQRT_DX) || (x == POP_DX) || (x == INC_DX) || (x == DEC_DX))
	{
		if (x == IN_DX)
		{
			printf("ENTER NUMBER (DX):\n");
		}
		return &dx;
	}
	return nullptr;
}
bool CPU::IN_()
{
	int command = China.return_com(num);
	if (command == IN_S)
	{
		while (true)
		{
			printf("ENTER NUMBER (STACK):\n");
			int n = 0;
			if (scanf("%d", &n) != 0)
			{
				Stack_CPU.push(n);
				print();
				return true;
			}
			else
			{
				printf("It's not a number, try again.\n");
			}
		}
	}
	if (command == IN_V)
	{
		while (true)
		{
			int x = Variable_.at(num);
			printf("ENTER NUMBER (VAR, num %d):\n", x);
			int n;
			if (scanf("%d", &n) != 0)
			{
				Variable_.at(num) = n;
				print();
				return true;
			}
			else
			{
				printf("It's not a number, try again.\n");
			}
		}
	}
	int* xx = Choose_Reg(command);
	if (xx != nullptr)
	{
		while (true)
		{
			int this_word;
			if (scanf("%d", &this_word) != 0)
			{
				*xx = this_word;
				print();
				return true;
			}
			else
			{
				printf("It's not a number, try again.\n");
				return false;
			}
		}
	}
	printf("error - in\n");
	return false;
}
bool CPU::POP_()
{
	int command = China.return_com(num);
	if (command == POP_S)
	{	
		if (!Stack_CPU.empty())
		{
			Stack_CPU.pop();
			print();
			return true;
		}
		else
		{
			printf("Stack - empty - pop\n");
			print();
			return false;
		}
	}
	if (command == POP_V)
	{
		Variable_.at(China.return_numbers(num)) = Stack_CPU.pop();
		return true;
	}
	int* xx = Choose_Reg(command);
	if (xx != nullptr)
	{
		if (!Stack_CPU.empty())
		{
			*xx = Stack_CPU.pop();
			print();
			return true;
		}
		else
		{
			printf("Stack - empty - pop\n");
			print();
			return false;
		}
	}
	printf("error - pop\n");
	return false;
}
bool CPU::DEC_()
{
	int command = China.return_com(num);
	if (command == DEC_S)
	{
		command = Stack_CPU.pop();
		command--;
		Stack_CPU.push(command);
		print();
		return true;
	}
	if (command == DEC_V)
	{
		Variable_T::iterator it = Variable_.find(China.return_numbers(num));
		if (it != Variable_.end())
		{
			Variable_[num]--;
		}
		else
		{
			printf("Error - var not declarated\n");
			return false;
		}
		return true;
	}
	int* xx = Choose_Reg(command);
	if (xx != nullptr)
	{
		*xx--;
		print();
		return true;
	}
	printf("error - dec\n");
	return false;
}
bool CPU::INC_()
{
	int command = China.return_com(num);
	if (command == INC_S)
	{
		command = Stack_CPU.pop();
		command++;
		Stack_CPU.push(command);
		print();
		return true;
	}
	if (command == INC_V)
	{
		Variable_T::iterator it = Variable_.find(China.return_numbers(num));
		if (it != Variable_.end())
		{
			Variable_.at(num)++;
		}
		else
		{
			printf("Error - var not declarated\n");
			return false;
		}
		return true;
	}
	int* xx = Choose_Reg(command);
	if (xx != nullptr)
	{
		*xx++;
		print();
		return true;
	}
	printf("error - inc\n");
	return false;
}
bool CPU::PUSH_()
{
	int command = China.return_com(num);
	if (command == PUSH_S)
	{
		Stack_CPU.push(China.return_numbers(num));
		print();
		return true;
	}
	if (command == PUSH_V)
	{
		Stack_CPU.push(Variable_.at(China.return_numbers(num)));
		print();
		return true;
	}
	int* xx = Choose_Reg(command);
	if (xx != nullptr)
	{
		if (!Stack_CPU.empty())
		{
			command = Stack_CPU.pop();
			*xx = command;
			print();
			return true;
		}
		else
		{
			printf("Error - Stack - push - empty\n");
			print();
			return false;
		}
	}
	printf("error - push\n");
	return false;
}
bool CPU::SQRT_()
{
	int command = China.return_com(num);
	if (command == SQRT_S)
	{
		command = Stack_CPU.pop();
		if (command > 0)
		{
			Stack_CPU.push(sqrt(command));
		}
		else
		{
			printf("Error - sqrt - <0");
			print();
			return false;
		}
		print();
		return true;
	}
	if (command == SQRT_V)
	{
		Variable_T::iterator it = Variable_.find(China.return_numbers(num));
		if (it != Variable_.end())
		{
			int x = Variable_.at(num);
			Variable_.at(num) = sqrt(x);
		}
		else
		{
			printf("Error - var not declarated\n");
			return false;
		}
		return true;
	}
	int* xx = Choose_Reg(command);
	if (xx != nullptr)
	{
		if (*xx > 0)
		{
			*xx = sqrt(*xx);
		}
		else
		{
			printf("Error - sqrt - <0");
			print();
			return false;
		}
		print();
		return true;
	}
	printf("error - sqrt\n");
	return false;
}

bool compNA(int a, int b) { return a >= b; }
bool compA(int a, int b) { return a > b; }
bool compB(int a, int b) { return a < b; };
bool compNB(int a, int b) { return a <= b; };
bool compE(int a, int b) { return a == b; };
bool compNE(int a, int b) { return a != b; };
bool CPU::conditionJump(CompFunction comp, string nameOfOperation)
{
	int x = Mrakobesie.return_numbers(num);
	if (Stack_CPU.size() > 2)
	{
		int tmp1 = Stack_CPU.pop();
		int tmp2 = Stack_CPU.pop();
		if (comp(tmp1, tmp2))
		{
			if (x < Mrakobesie.size_type())
			{
				num = x - 1;
			}
			else
			{
				printf("Error - ");
				printf("%s - ", nameOfOperation.c_str());
				printf("empty\n");
				return false;
			}
		}
		Stack_CPU.push(tmp2);
		Stack_CPU.push(tmp1);
		return true;
	}
	else
	{
		printf("Error - ");
		printf("%s - ", nameOfOperation.c_str());
		printf("empty\n");
		print();
		return false;
	}
}

bool CPU::JMP_L()
{
	int x = Mrakobesie.return_numbers(num);
	if (x < Mrakobesie.size_type())
	{
		num = x - 1;
		return true;
	}
	else
	{
		printf("Error - jmp\n");
		print();
		return false;
	}
}
bool CPU::J_A_L()
{
	if (conditionJump(compA, "ja"))
		return true;
	else
		return false;
}
bool CPU::J_NA_L()
{
	if (conditionJump(compNA, "jna"))
		return true;
	else
		return false;
}
bool CPU::J_NB_L()
{
	if (conditionJump(compNB, "jnb"))
		return true;
	else
		return false;
}
bool CPU::J_B_L()
{
	if (conditionJump(compB, "jb"))
		return true;
	else
		return false;
}
bool CPU::J_E_L()
{
	if (conditionJump(compE, "je"))
		return true;
	else
		return false;
}
bool CPU::J_NE_L()
{
	if (conditionJump(compNE, "jne"))
		return true;
	else
		return false;
}

bool CPU::CALL_A_F()
{
	if (conditionJump(compA, "calla"))
	{
		of_Function.push(num);
		return true;
	}
	else
		return false;
}
bool CPU::CALL_NA_F()
{
	if (conditionJump(compNA, "callna"))
	{
		of_Function.push(num);
		return true;
	}
	else
		return false;
}
bool CPU::CALL_B_F()
{
	if (conditionJump(compB, "callb"))
	{
		of_Function.push(num);
		return true;
	}
	else
		return false;
}
bool CPU::CALL_NB_F()
{
	if (conditionJump(compNB, "callnb"))
	{
		of_Function.push(num);
		return true;
	}
	else
		return false;
}
bool CPU::CALL_E_F()
{
	if (conditionJump(compE, "calle"))
	{
		of_Function.push(num);
		return true;
	}
	else
		return false;
}
bool CPU::CALL_NE_F()
{
	if (conditionJump(compNE, "callne"))
	{
		of_Function.push(num);
		return true;
	}
	else
		return false;
}
bool CPU::CALL_F()
{
	int x = Mrakobesie.return_numbers(num);
	if (x < Mrakobesie.size_type())
	{
		of_Function.push(num);
		num = x - 1;
		return true;
	}
	else
	{
		printf("Error - call\n");
		print();
		return false;
	}
}