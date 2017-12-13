#pragma once

#define CONST 0
#define VAR 1
#define ARR 2
#define PROC 3
#define FUNC 4
#define PARA 5
#define LABEL 6
#define VAL 7
#define CALL 8
#define LARR 9
#define SARR 10
#define JZ 11
#define JNZ 12
#define SCAN 13
#define PRINTS 14
#define PRINTI 15
#define PRINTC 16
#define RET 17
#define PLUS 18
#define MINUS 19
#define TIMES 20
#define DIVIDE 21
#define EQU 22
#define LES 23
#define LEQ 24
#define GTR 25
#define GEQ 26
#define NEQ 27
#define ASN 28
#define DEL 29

struct Quadruple {
	int op;
	char op1[IdentityMaxLen];
	char op2[IdentityMaxLen];
	char res[IdentityMaxLen];
};

void GenerateMidCode(int op, char op1[], char op2[], char res[]);

char* Type2String(int type);
char* Int2String(int value);
int NewTempVar();
char* TempVar(int num);
int NewLabel();
char* Label(int num);