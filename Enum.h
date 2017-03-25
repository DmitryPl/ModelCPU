#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "iostream"
#include "algorithm"

using std::string;

const int MAX_CMD_SIZE = 16;
const int MAX_PATH_SIZE = 128;
const int SUCCESS = 42;

enum Commands_ASM
{
	ADD = 10, POP_AX, POP_BX, POP_DX, POP_CX, SIN, COS, DIV, SQRT, SUM, SUB, OUT, DEC, INC, LABEL, 
	PUSH, HMD, PUSH_AX, PUSH_BX, PUSH_CX, PUSH_DX, JA, JP, DED, JMP, JC, CALLA, CALLC, CALLP, RET, FUNC, IN_AX, IN_BX, IN_CX, IN_DX
};

class CPU;
typedef bool(CPU::*MyFuncType)(int);

#define CHECK_CMD(STR, CONST) if(STR == word) { word = getStrFromNumber(CONST) ; num++; return word; } 
#define COMMANDS_TO_JMP(STR, CONST) if(STR == word) { if(Marker(word, list)) { word = getStrFromNumber(CONST) ; num++; return word;} else return "0"; }
#define COMMANDS_TO_JMP_F(STR, CONST) if(STR == word) { if(Marker_F(word, list)) { word = getStrFromNumber(CONST) ; num++; return word;} else return "0"; }
#define CHECK_CPU(NUM, CONST, POINTER) if(NUM == CONST) { MyFuncType res = &CPU::POINTER; return &res; }
#define CHECK_CPU_F(NUM, CONST, POINTER) if(NUM == CONST) { Arrayer(); MyFuncType res = &CPU::POINTER; return &res; }
#define HELP "\nCommands:\n\n\
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

