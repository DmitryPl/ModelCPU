#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "CPU.h"
#include "ASM.h"
#include "DASM.h"
		
void main()
{
	DASM Disassembler;
	ASM Socialism;
	CPU Ñommunism;

	const char* a = Socialism.Dialog();
	if (a)
	{
		getch();
		if (Ñommunism.CPU_(a))
		{
			int i = Disassembler.Dialog(a);
			switch (i)
			{
			case  1: fprintf(stderr, "\nEND DASM\n");
				break;
			case -1: doNothing();
				break;
			case  0: fprintf(stderr, "\nERROR DASM\n");
				break;
			default: fprintf(stderr, "\nERROR DASM\n");
				break;
			}
		}
		else
		{
		fprintf(stderr, "\nERROR CPU\n");
		}
	}
	else
	{
		fprintf(stderr, "\nERROR ASM\n");
	}
	fprintf(stderr, "\nPress the button.\n");
	getch();
}