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
	char src[IdentityMaxLen];
	char res[IdentityMaxLen];
	char path[IdentityMaxLen];
	scanf("%s", src);
	strcpy_s(path, src);
	int len = strnlen_s(path, IdentityMaxLen);
	while (len > 0)
		if (path[--len] == '\\')
			break;
	path[len == 0 ? len : len + 1] = '\0';
	fopen_s(&source, src, "r");
	if (source == NULL) {
		Error(FILE_NOT_EXIST_ERROR);
		exit(0);
	}
	strcpy_s(res, path);
	strcat_s(res, "record.txt");
	fopen_s(&compilerecord, res, "w");
	strcpy_s(res, path);
	strcat_s(res, "table.txt");
	fopen_s(&tablerecord, res, "w");
	
	Program();
	if (success) {
		strcpy_s(res, path);
		strcat_s(res, "midcode_origin.txt");
		fopen_s(&middlecode, res, "w");
		QuadrupleTest();
		strcpy_s(res, path);
		strcat_s(res, "targetcode_origin.asm");
		fopen_s(&targetcode, res, "w");
		GenerateMIPS32();
		fclose(targetcode);
		DeleteInvalidCode();
		ConstantCombination();
		CommonSubexpressionElimination();
		ClearUnusedVar();
		AllocGlobalReg();
		AllocTempReg();
		strcpy_s(res, path);
		strcat_s(res, "midcode.txt.txt");
		fopen_s(&middlecode, res, "w");
		QuadrupleTest();
		fclose(middlecode);
		strcpy_s(res, path);
		strcat_s(res, "targetcode.asm");
		fopen_s(&targetcode, res, "w");
		GenerateMIPS32();
		fclose(targetcode);
		printf("Compile successfully.\n");
	}
	else
		printf("Compile failed.\n");
	fclose(source);
	fclose(compilerecord);
	fclose(tablerecord);
	return 0;
}