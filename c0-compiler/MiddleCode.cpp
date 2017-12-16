#include "stdafx.h"

Quadruple midcode[CodeMaxNum];
int cnt = 0;
int tmp_num = 0;
int lab_num = -1;

int rec = 0;
char res1[15];
char res2[15];
char res3[15];

void GenerateMidCode(int op, char op1[], char op2[], char res[]) {
	midcode[cnt].op = op;
	strcpy_s(midcode[cnt].op1, op1);
	strcpy_s(midcode[cnt].op2, op2);
	strcpy_s(midcode[cnt].res, res);
	cnt++;
}

char* Type2String(int type) {
	if (type == INT)
		return "int";
	if (type == CHAR)
		return "char";
	return "";
}
char* Int2String(int value) {
	_itoa_s(value, res1, 10);
	return res1;
}
int NewTempVar() {
	return ++tmp_num;
}
char* TempVar(int num) {
	char tmp[10];
	strcpy_s(res2, "$tmp");
	_itoa_s(num, tmp, 10);
	strcat_s(res2, tmp);
	return res2;
}
int NewLabel() {
	return ++lab_num;
}
char* Label(int num) {
	char tmp[10];
	strcpy_s(res3, "$lab");
	_itoa_s(num, tmp, 10);
	strcat_s(res3, tmp);
	return res3;
}