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

int main()
{
	ASM Assembler;
	const char* a = Assembler.Dialog();
	if (a)
	{
		fprintf(stderr, "\nPress the button.\n");
		getch();
	}
}