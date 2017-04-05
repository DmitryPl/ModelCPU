#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "ASM.h"
		
void main()
{
	ASM Socialism;
	const char* a = Socialism.Dialog();
	if (a)
	{
		fprintf(stderr, "\nPress the button.\n");
		getch();
	}
	else
	{
		fprintf(stderr, "\nERROR ASM\n");
		getch();
	}
}