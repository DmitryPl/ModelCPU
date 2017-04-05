#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "DASM.h"

void Files_Main(char* buffer);

void main(int argc, char* argv[])
{
	printf("Running from %s\n", argv[0]);
	printf("\nSTARTING DASM\n");
	DASM Disassembler;
	char output[MAX_PATH_SIZE] = "";
	Files_Main(output);
	int i = Disassembler.Dialog(output);
	switch (i)
	{
	case  1: fprintf(stderr, "\nEND DASM\n"); getch();
		break;
	case -1: doNothing(); getch();
		break;
	case  0: fprintf(stderr, "\nERROR DASM\n"); getch();
		break;
	default: fprintf(stderr, "\nERROR DASM\n"); getch();
		break;
	}
}

void Files_Main(char* buffer)
{
	printf("\nEnter \"S\" to use standart file output.txt\n or enter way to directory like \"D:\\output.txt\"\n");
	scanf("%s", buffer);
	if (!strcmp("S", buffer))
	{
		strcpy(buffer, "output.txt");
	}
}