#pragma once

#define CHECK_CMD(STR, CONST) if(STR == word) { word = getStrFromNumber(CONST) ; num++; return word; } 
#define COMMANDS_TO_JMP(STR, CONST) if(STR == word) { if(Marker(word, list)) { word = getStrFromNumber(CONST) ; num++; return word;} else return "0"; }


enum Commands_ASM
{
	ADD = 10, POP_AX, POP_BX, POP_DX, POP_CX, SIN, COS, DIV, SQRT, SUM, SUB, OUT, DEC, INC, LABEL, 
	PUSH, HMD, PUSH_AX, PUSH_BX, PUSH_CX, PUSH_DX, JA, JP, DED, JMP, JC, CALLA, CALLC, CALLP, RET
};