#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "iostream"
#include "algorithm"

class List;
using std::string;

class CPU;
typedef bool(CPU::*MyFuncType)();

const int MAX_CMD_SIZE = 16;
const int MAX_PATH_SIZE = 128;
const int SUCCESS = 42;

enum Commands_ASM
{
	ADD_D = 10, POP_AX, POP_BX, POP_DX, POP_CX, DIV_S, MUL_V, MUL_S, OUT, DEC_S, INC_S, LABEL, VAR_D, 
	PUSH_S, HALT, PUSH_AX, PUSH_BX, PUSH_CX, PUSH_DX, DED, JMP, RET, J_E, J_NE, J_A, J_NA, J_B, J_NB, FUNC,
	IN_AX, IN_BX, IN_CX, IN_DX, IN_S, DEC_AX, DEC_BX, DEC_CX, DEC_DX, INC_AX, INC_BX, INC_CX, INC_DX, MOV_D,
	CALL, CALL_E, CALL_NE, CALL_A, CALL_NA, CALL_B, CALL_NB, VAR, IN_V, PUSH_V, DEC_V, INC_V, POP_S, POP_V,
	SQRT_S, SQRT_AX, SQRT_BX, SQRT_CX, SQRT_DX, SQRT_V, ADD_S, DIV_D, SUB_D, MUL_D, SUB_S
};

enum Registr
{
	AX = 1, BX, CX, DX
};

#define HELP "It's old version of help. \nCommands:\n\n\
div - /             pop ax - stack->ax\n\
sub - -             pop bx - stack->bx\n\
sum - *             pop cx - stack->cx\n\
add - +             pop dx - stack->dx\n\
ja  - >             sqrt - top of stack->stack\n\
jc - ==             out - print all\n\
jp - <=             ded - SPACE\n\
jmp - jmp           hmd - stop\n\
label : label       sin - top of stack->CON\n\
jmp label :         cos - top of stack->CON\n\
dec - dx--          in ax - write ax from CON\n\
inc - dx++          in bx - write bx from CON\n\
push(n) - to stack  in cx - write cx from CON\n\
push dx - to dx     in dx - write dx from CON\n\
push ax - to ax     call(a - p) - call func\n\
push cx - to cx     func : func - in func\n\
push dx - to dx     ret - out func\n\
exit - stop writting ASM, works and(in), and(file)"

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

int doNothing() //The most optimistic function ever
{
	return SUCCESS;
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

