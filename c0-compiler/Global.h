#pragma once

enum Symbol {
	voidsym,	//void
	intsym,		//int
	charsym,	//char
	mainsym,	//main
	dosym,		//do
	whilesym,	//while
	ifsym,		//if
	switchsym,	//switch
	casesym,	//case
	constsym,	//const
	scanfsym,	//scanf
	printfsym,	//printf
	returnsym,	//return
	identity,	//��ʶ��
	intconst,	//���ͳ���
	charconst,	//�ַ�����
	stringconst,//�ַ�������
	plus,		//+
	minus,		//-
	times,		//*
	divide,		///
	lpare,		//(
	rpare,		//)
	lbrak,		//[
	rbrak,		//]
	lbrac,		//{
	rbrac,		//}
	assign,		//=
	equ,		//==
	les,		//<
	gtr,		//>
	leq,		//<=
	geq,		//>=
	neq,		//!=
	comma,		//,
	colon,		//:
	semic,		//;
	none
};
const int SymbolNum = 38;

const int KeyWordNum = 13;
const char KeyWord[KeyWordNum][10] = {
	"void", "int", "char", "main", "do",
	"while", "if", "switch", "case", "const",
	"scanf", "printf", "return"
};

const int GlobalSize = 1024;
const int LocalSize = 32768;
const int ParaMaxNum = 20;
const int IdentityMaxLen = 1024;
const int CodeMaxLen = 512;
const int CodeMaxNum = 32768;

void LexicalTest();
void SyntaxTest(int code);
void LocalTableTest();
void GlobalTableTest();
void QuadrupleTest(bool isOpti);