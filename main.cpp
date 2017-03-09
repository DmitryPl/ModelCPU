#pragma once

#include <cstdio>
#include "conio.h"
#include <cstdlib>
#include <cassert>
#include <cstring>
#include "CPU.h"
#include "ASM.h"

int main()
{
	ASM Assembler;
	const char* a = Assembler.Dialog();
	if (a)
	{
		fprintf(stderr, "Press the button.\n", "w");
		getch();
	}
}