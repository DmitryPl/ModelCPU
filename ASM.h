#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"

#define CHECK_CMD(STR, FUNC) if(strcmp(STR, word) == 0) { FUNC; return true; }

enum Commands	{ ADD = 50, PUSH, POP, SIN, COS, DIV, SQRT, SUM, SUB, HMD };
enum Register	{ N = 1, L, S, D };
enum CPU		{ AX = 20, BX, CX, DX };

//Are you sure with return? No. And pp???

const int MAX_CMD_SIZE = 16;
const int MAX_PATH_SIZE = 128;
const int SUCCESS = 100500;

int  Dialog();
int  Files();
bool Assembler();
bool IsItNumber(char* word);
bool Commands(char* word);
bool Pusher();
bool CommandsCPU(char* this_word);
int  doNothing();

int  Dialog()
{
	int a;
	printf("If you want to work with files enter \"file\". If you want to enter commands from console enter \"in\".\n");
	char request[MAX_CMD_SIZE] = "";
	scanf("%s", request);
	if (strcmp("file", request) == 0)
	{
		a = Files();
		Assembler();
		return a;
	}
	else if (strcmp("in", request) == 0)
	{
		if (!freopen("output.txt", "w", stdout))
		{
			printf("Error - ASM - In\n");
			return 0;
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
		return 1;
	}
	else
	{
		printf("Error - ASM - else\n");
		return 0;
	}
}

int  Files()
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
	return (*output_path);
}

bool Assembler()
{
	while (!feof(stdin))
	{
		char word[MAX_CMD_SIZE] = "";
		scanf("%s", word);
		fprintf(stderr, "Scanf has read: %s\n", word);//Waaagh!
		getch();
		if (strcmp("exit", word) == 0)
		{
			return false;
		}
		if (Commands(word))
		{
			if (doNothing() != SUCCESS)
			{
				printf("You can't even do nothing. Go away\n");
			}
		}
		else
		{
			fprintf(stderr, "It's not a command. Start again\nYou can press exit or ignore this problem\n", word);
			getch();
		}
	}
}

bool IsItNumber(char* word)
{
	size_t i = 0;
	while (word[i] != '\0')
	{
		if (!isdigit(word[i++]))
			return false;
	}
	return true;
}

bool Commands(char* word)
{
	CHECK_CMD("hmd", printf("%d ", HMD));
	CHECK_CMD("pop", printf("%d ", POP));
	CHECK_CMD("add", printf("%d ", ADD));
	CHECK_CMD("sin", printf("%d ", SIN));
	CHECK_CMD("cos", printf("%d ", COS));
	CHECK_CMD("sqrt", printf("%d ", SQRT));
	CHECK_CMD("sum", printf("%d ", SUM));
	CHECK_CMD("sub", printf("%d ", SUB));
	if (strcmp("push", word) == 0)
	{
		if (Pusher())
		{
			return true;
		}
		else return false;
	}
	else
	{
		return false;
	}
}

bool Pusher()
{
	char this_word[MAX_CMD_SIZE] = "";
	scanf("%s", this_word);

	if (IsItNumber(this_word))
	{
		fprintf(stderr, "Scanf has read: %s\n", this_word);
		getch();
		printf("%d %d %s ", PUSH, N, this_word);
		return true;
	}
	if (CommandsCPU(this_word))
	{
		fprintf(stderr, "Scanf has read: %s\n", this_word);
		getch();
		return true;
	}
	else
	{
		fprintf(stderr, "It's not a command. Start again\n", this_word);
	}
}

bool CommandsCPU(char* word)
{
	CHECK_CMD("cx", printf("%d %d %d ", PUSH, L, CX));
	CHECK_CMD("ax", printf("%d %d %d ", PUSH, L, AX));
	CHECK_CMD("dx", printf("%d %d %d ", PUSH, L, DX));
	CHECK_CMD("bx", printf("%d %d %d ", PUSH, L, BX));
}

int  doNothing()
{
	return SUCCESS;
}
