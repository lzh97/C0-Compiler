#include "stdafx.h"

extern Symbol symbol;
extern char id[IdentityMaxLen];
extern int len;
extern char ch;
extern int num;

extern char line[CodeMaxLen];
extern int ll;
extern int cc;
extern int lc;
extern int ln;

extern FILE *source;

void NextChar();
void Retract();
bool isUseless();
bool isNumber(int l, int r);
bool isPlus();
bool isMinus();
bool isTimes();
bool isDivide();
bool isLpare();
bool isRpare();
bool isLbrak();
bool isRbrak();
bool isLbrac();
bool isRbrac();
bool isSquot();
bool isDquot();
bool isEqu();
bool isLes();
bool isGtr();
bool isExc();
bool isComma();
bool isColon();
bool isSemic();
void ToLower();
Symbol CheckKeyWord();

void NextSymbol() {
	lc = ln;
	NextChar();
	while (isUseless())
		NextChar();
	if (isLetter()) {
		len = 0;
		do {
			id[len++] = ch;
			NextChar();
		} while (isLetter() || isNumber(0, 9));
		id[len] = '\0';
		ToLower();
		Retract();
		symbol = CheckKeyWord();
	}
	else if (isNumber(0, 0)) {
		num = 0;
		NextChar();
		if (isNumber(0, 9)) {
			Warning(LEADING_ZERO_WARNING);
			while (isNumber(0, 9)) {
				num = num * 10 + (ch - '0');
				NextChar();
			}
		}
		Retract();
		symbol = intconst;
	}
	else if (isNumber(1, 9)) {
		num = 0;
		do {
			num = num * 10 + (ch - '0');
			NextChar();
		} while (isNumber(0, 9));
		Retract();
		symbol = intconst;
	}
	else if (isPlus())
		symbol = plus;
	else if (isMinus())
		symbol = minus;
	else if (isTimes())
		symbol = times;
	else if (isDivide())
		symbol = divide;
	else if (isLpare())
		symbol = lpare;
	else if (isRpare())
		symbol = rpare;
	else if (isLbrak())
		symbol = lbrak;
	else if (isRbrak())
		symbol = rbrak;
	else if (isLbrac())
		symbol = lbrac;
	else if (isRbrac())
		symbol = rbrac;
	else if (isSquot()) {
		len = 0;
		while (true) {
			NextChar();
			if (isSquot())
				break;
			else if (isLetter() || isNumber(0, 9) || isPlus() || isMinus() || isTimes() || isDivide())
				id[len++] = ch;
			else
				Error(INVALID_CHARACTER_ERROR);
		}
		id[len] = '\0';
		if (len != 1) {
			Error(CHARACTER_LENGTH_ERROR);
			if (len == 0) {
				id[0] = CHAR_INIT;
				id[1] = '\0';
			}
		}
		symbol = charconst;
	}
	else if (isDquot()) {
		len = 0;
		while (true) {
			NextChar();
			if (isDquot())
				break;
			else if (ch >= 32 && ch <= 126)
				id[len++] = ch;
			else
				Error(INVALID_CHARACTER_ERROR);
		}
		id[len] = '\0';
		symbol = stringconst;
	}
	else if (isEqu()) {
		NextChar();
		if (isEqu())
			symbol = equ;
		else {
			Retract();
			symbol = assign;
		}
	}
	else if (isLes()) {
		NextChar();
		if (isEqu())
			symbol = leq;
		else {
			Retract();
			symbol = les;
		}
	}
	else if (isGtr()) {
		NextChar();
		if (isEqu())
			symbol = geq;
		else {
			Retract();
			symbol = gtr;
		}
	}
	else if (isExc()) {
		NextChar();
		if (!isEqu()) {
			Retract();
			Error(INVALID_SYMBOL_ERROR);
		}
		symbol = neq;
	}
	else if (isComma())
		symbol = comma;
	else if (isColon())
		symbol = colon;
	else if (isSemic())
		symbol = semic;
	else {
		Error(INVALID_SYMBOL_ERROR);
		symbol = none;
		NextSymbol();
	}
	LexicalTest();
}

void NextChar() {
	char tmp;
	if (cc >= ll) {
		if ((tmp = fgetc(source)) == EOF) {		//程序不完整报错
			Error(PROGRAM_INCOMPLETE_ERROR);
			exit(0);
		}
		ll = cc = 0;
		while (true) {
			if (tmp == '\n' || tmp == EOF) {
				ln++;
				break;
			}
			line[ll++] = tmp;
			tmp = fgetc(source);
		}
		line[ll++] = ' ';
	}
	ch = line[cc++];
}
void Retract() {
	ch = line[--cc - 1];
}
bool isUseless() {
	return ch == ' ' || ch == '\t' || ch == '\n' ? true : false;
}
bool isLetter() {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') ? true : false;
}
bool isNumber(int l, int r) {
	return ch >= '0' + l && ch <= '0' + r ? true : false;
}
bool isPlus() {
	return ch == '+' ? true : false;
}
bool isMinus() {
	return ch == '-' ? true : false;
}
bool isTimes() {
	return ch == '*' ? true : false;
}
bool isDivide() {
	return ch == '/' ? true : false;
}
bool isLpare() {
	return ch == '(' ? true : false;
}
bool isRpare() {
	return ch == ')' ? true : false;
}
bool isLbrak() {
	return ch == '[' ? true : false;
}
bool isRbrak() {
	return ch == ']' ? true : false;
}
bool isLbrac() {
	return ch == '{' ? true : false;
}
bool isRbrac() {
	return ch == '}' ? true : false;
}
bool isSquot() {
	return ch == '\'' ? true : false;
}
bool isDquot() {
	return ch == '"' ? true : false;
}
bool isEqu() {
	return ch == '=' ? true : false;
}
bool isLes() {
	return ch == '<' ? true : false;
}
bool isGtr() {
	return ch == '>' ? true : false;
}
bool isExc() {
	return ch == '!' ? true : false;
}
bool isComma() {
	return ch == ',' ? true : false;
}
bool isColon() {
	return ch == ':' ? true : false;
}
bool isSemic() {
	return ch == ';' ? true : false;
}
void ToLower() {
	for (int i = 0; i < len; i++)
		if (id[i] >= 'A' && id[i] <= 'Z')
			id[i] = id[i] - 'A' + 'a';
}
Symbol CheckKeyWord() {
	for (int i = 0; i < KeyWordNum; i++)
		if (strcmp(id, KeyWord[i]) == 0)
			return (Symbol)i;
	return (Symbol)KeyWordNum;
}