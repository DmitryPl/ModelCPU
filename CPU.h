#pragma once

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "string"
#include "Stack.h"
#include "Enum.h"

class CPU
{
private:
	int* Register_;
	Stack Commands_;

public:
	void CPU_(char* output);
};


void CPU::CPU_(char* output)
{
	//
}