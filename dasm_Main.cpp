#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "DASM.h"
		
const char* Files_Main();

void main(int argc, char* argv[])
{
	printf("Running from %s\n", argv[0]);
	printf("\nSTARTING DASM\n");
	DASM Disassembler;
	int i = Disassembler.Dialog(Files_Main());
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

const char* Files_Main()
{
	char output[MAX_PATH_SIZE] = "";
	printf("\nEnter \"S\" to use standart file output.txt\n or enter way to directory like \"D:\\output.txt\"\n");
	scanf("%s", output);
	const char* output_path = strcmp("S", output) ? output : "output.txt";
	return output_path;
}