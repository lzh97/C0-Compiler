// c0-compiler.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"

Symbol symbol;
char id[IdentityMaxLen];
int len;
char ch;
int num;

Identity global[GlobalSize], local[LocalSize];
int gsize = 0, lsize = 0;

char line[CodeMaxLen];
int ll = 0;
int cc = 0;
int lc = 1;
int ln = 0;

bool success = true;

FILE *source;
FILE *compilerecord;
FILE *tablerecord;
FILE *middlecode_o;
FILE *middlecode;
FILE *targetcode;

int _tmain(int argc, _TCHAR* argv[]) {
	char filepath[IdentityMaxLen];
	scanf("%s", filepath);
	fopen_s(&source, filepath, "r");
	if (source == NULL) {
		Error(FILE_NOT_EXIST_ERROR);
		exit(0);
	}
	fopen_s(&compilerecord, "record.txt", "w");
	fopen_s(&tablerecord, "table.txt", "w");
	fopen_s(&middlecode_o, "midcode_origin.txt", "w");
	fopen_s(&middlecode, "midcode.txt", "w");
	int len = strnlen_s(filepath, IdentityMaxLen);
	while (len > 0)
		if (filepath[--len] == '.')
			break;
	filepath[len] = '\0';
	strcat_s(filepath, ".asm");
	fopen_s(&targetcode, filepath, "w");
	Program();
	if (success) {
		QuadrupleTest(false);
		CommonSubexpressionElimination();
		//ConstantReplace();
		QuadrupleTest(true);
		GenerateMIPS32();
		printf("Compile successfully.\n");
	}
	else
		printf("Compile failed.\n");
	fclose(source);
	fclose(compilerecord);
	fclose(tablerecord);
	fclose(middlecode);
	fclose(middlecode_o);
	return 0;
}