#pragma once

#define DATASIZE 4
#define at 1
#define v0 2
#define v1 3
#define a0 4
#define a1 5
#define a2 6
#define a3 7
#define t0 8
#define t1 9
#define t2 10
#define t3 11
#define t4 12
#define t5 13
#define t6 14
#define t7 15
#define s0 16
#define s1 17
#define s2 18
#define s3 19
#define s4 20
#define s5 21
#define s6 22
#define s7 23
#define t8 24
#define t9 25
#define k0 26
#define k1 27
#define gp 28
#define sp 29
#define fp 30
#define ra 31

const unsigned int dba = 0x10010000;	//数据基地址
const unsigned int sba = 0x7ffffffc;	//栈基地址

const char reg[32][4] = {
	"$0",		//0
	"$at",		//1
	"$v0",		//2
	"$v1",
	"$a0",		//4
	"$a1",
	"$a2",
	"$a3",
	"$t0",		//8
	"$t1",
	"$t2",
	"$t3",
	"$t4",
	"$t5",
	"$t6",
	"$t7",
	"$s0",		//16
	"$s1",
	"$s2",
	"$s3",
	"$s4",
	"$s5",
	"$s6",
	"$s7",
	"$t8",		//24
	"$t9",
	"$k0",		//26
	"$k1",
	"$gp",		//28
	"$sp",		//29
	"$fp",		//30
	"$ra"		//31
};

void GenerateMIPS32();