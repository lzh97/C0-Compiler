#pragma once

#define CONSTANT 0			//����
#define VARIABLE 1			//����
#define PARAMETER 2			//����
#define PROCEDURE 3			//����
#define FUNCTION 4			//����
#define ARRAY 5				//����
#define DELETED 6			//ɾ��

#define INT 0				//����
#define CHAR 1				//�ַ���

#define INT_INIT 0			//���ͳ�ʼֵ
#define CHAR_INIT '_'		//�ַ��ͳ�ʼֵ

struct Identity {
	char name[IdentityMaxLen];	//����
	int kind;					//����
	int type;					//����
	int value;					//ֵ
	int addr;					//��ַ
	bool isglobal;
	unsigned int hash;

	int	size;					//�����С|��������
	unsigned int paratype;		//��������
	int l, r;					//�ֲ���������
};

Identity* AddConst(char name[], int type, int value, bool isglobal);
void AddArray(char name[], int type, int size, bool isglobal);
Identity* AddVar(char name[], int type, bool isglobal);
Identity* AddFunc(char name[], int type);
Identity* AddProc(char name[]);
void AddPara(char name[], int type);
Identity* Search(char name[], int code);

unsigned int Hash(char *str);
