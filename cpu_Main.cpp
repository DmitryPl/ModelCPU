#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "CPU.h"
		
const char* Files_Main();

void main(int argc, char* argv[])
{
	printf("Running from %s\n", argv[0]);

	CPU Communism;
	if (Communism.Dialog(Files_Main()))
	{
		getch();
	}
	else
		printf("\nERROR CPU\n");
}

const char* Files_Main()
{
	char output[MAX_PATH_SIZE] = "";
	printf("\nEnter \"S\" to use standart file output.txt\n or enter way to directory like \"D:\\output.txt\"\n");
	scanf("%s", output);
	const char* output_path = strcmp("S", output) ? output : "output.txt";
	return output_path;
}