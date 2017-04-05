#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "CPU.h"
		
void Files_Main(char* buffer);

void main(int argc, char* argv[])
{
	printf("Running from %s\n", argv[0]);
	char output[MAX_PATH_SIZE] = "";
	Files_Main(output);

	CPU Communism;
	if (Communism.Dialog(output))
	{
		getch();
	}
	else
		printf("\nERROR CPU\n");
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