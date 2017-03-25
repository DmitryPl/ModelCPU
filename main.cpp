#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include <iostream>
#include "CPU.h"
#include "ASM.h"
		
void main()
{
	ASM Assembler;
	CPU Ñommunism;
	const char* a = "output.txt";//Assembler.Dialog();
	if (a)
	{
		fprintf(stderr, "\nPress the button.\n");
		getch();
		fprintf(stderr, "\nSTARTING CPU\n");
		if (Ñommunism.CPU_(a))
		{
			fprintf(stderr, "\nEND CPU\n");
			getch();
		}
		else
		{
		fprintf(stderr, "\nERROR CPU\n");
		}
	}
	getch();
}