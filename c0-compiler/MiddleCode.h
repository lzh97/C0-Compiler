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
#define J 11
#define JZ 12
#define JNZ 13
#define SCAN 14
#define PRINTS 15
#define PRINTI 16
#define PRINTC 17
#define RET 18
#define PLUS 19
#define MINUS 20
#define TIMES 21
#define DIVIDE 22
#define EQU 23
#define LES 24
#define LEQ 25
#define GTR 26
#define GEQ 27
#define NEQ 28
#define ASN 29
#define DEL 30

struct Quadruple {
	int op;
	char op1[IdentityMaxLen];
	char op2[IdentityMaxLen];
	char res[IdentityMaxLen];
};

void GenerateMidCode(int op, char op1[], char op2[], char res[]);
void GenerateTempCode(int op, char op1[], char op2[], char res[]);

char* Type2String(int type);
char* Int2String(int value);
int NewTempVar();
char* TempVar(int num);
int NewLabel();
char* Label(int num);