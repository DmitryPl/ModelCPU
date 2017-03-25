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

