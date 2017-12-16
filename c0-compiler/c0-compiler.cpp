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
FILE *middlecode;
FILE *targetcode;

int _tmain(int argc, _TCHAR* argv[]) {
	char filepath[IdentityMaxLen] = "15061140_test.txt";
	//scanf("%s", filepath);
	fopen_s(&source, filepath, "r");
	fopen_s(&compilerecord, "15061140_record.txt", "w");
	fopen_s(&tablerecord, "15061140_table.txt", "w");
	fopen_s(&middlecode, "15061140_midcode.txt", "w");
	int len = strnlen_s(filepath, IdentityMaxLen);
	filepath[len - 4] = '\0';
	strcat_s(filepath, ".asm");
	fopen_s(&targetcode, filepath, "w");
	if (source == NULL) {
		Error(FILE_NOT_EXIST_ERROR);
		exit(0);
	}
	Program();
	if (success) {
		GenerateMIPS32();
		printf("Compile successfully.\n");
	}
	else
		printf("Compile failed.\n");
	QuadrupleTest();
	fclose(source);
	fclose(compilerecord);
	fclose(tablerecord);
	fclose(middlecode);
	return 0;
}