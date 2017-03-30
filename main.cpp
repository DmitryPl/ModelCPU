#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "CPU.h"
#include "ASM.h"
		
void main()
{
	ASM Socialism;
	CPU Ñommunism;
	const char* a = Socialism.Dialog();
	if (a)
	{
		getch();
		if (Ñommunism.CPU_(a))
		{
			doNothing();
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