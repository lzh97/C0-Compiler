#pragma once

#define CONSTANT 0			//常量
#define VARIABLE 1			//变量
#define PARAMETER 2			//参数
#define PROCEDURE 3			//过程
#define FUNCTION 4			//函数
#define ARRAY 5				//数组

#define INT 0				//整型
#define CHAR 1				//字符型

#define INT_INIT 0			//整型初始值
#define CHAR_INIT '_'		//字符型初始值

struct Identity {
	char name[IdentityMaxLen];	//名字
	int kind;					//种类
	int type;					//类型
	int value;					//值
	int addr;					//地址
	bool isglobal;
	unsigned int hash;

	int	size;					//数组大小|参数个数
	unsigned int paratype;		//参数类型
	int l, r;					//局部符号索引
};

void AddConst(char name[], int type, int value, bool isglobal);
void AddArray(char name[], int type, int size, bool isglobal);
Identity* AddVar(char name[], int type, bool isglobal);
Identity* AddFunc(char name[], int type);
Identity* AddProc(char name[]);
void AddPara(char name[], int type);
Identity* Search(char name[], int code);
