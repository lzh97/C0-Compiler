#include "stdafx.h"

NodeInfo nodetab[LocalSize];
Node nodes[LocalSize];

int tabnum = 0;
int nodenum = 0;

extern Quadruple tempcode[CodeMaxNum];
extern int temp_cnt;


void Link(int root, int lchild, int rchild);
int NewNode(char* name, int op);
void UpdateTab(char* name, int index);
int SearchIndex(char* name);
void AddNode_1(int op, char* op1, char* res);
void AddNode_2(int op, char* op1);
void AddNode_3(int op, char* res);
void AddNode_4(int op, char* op1, char* op2, char* res);
void AddNode_5(int op, char* op1, char* op2, char* res);
void AddNode_6(int op, char* op1, char* op2, char* res);
void AddNode_7(int op);
bool isSimpleArithmetic(int op);



void Link(int root, int lchild, int rchild) {
	nodes[root].lchild = lchild;
	nodes[root].rchild = rchild;
	if (lchild >= 0)
		nodes[lchild].parent_num++;
	if (rchild >= 0)
		nodes[rchild].parent_num++;
}

void UpdateTab(char* name, int index) {
	unsigned int hash = Hash(name);
	for (int i = 0; i < tabnum; i++)
		if (nodetab[i].hash == hash)
			if (strcmp(nodetab[i].name, name) == 0) {
				nodetab[i].index = index;
				return;
			}
	strcpy_s(nodetab[tabnum].name, name);
	nodetab[tabnum].hash = hash;
	nodetab[tabnum++].index = index;
}

int NewNode(char* name, int op) {
	nodes[nodenum].op = op;
	nodes[nodenum].parent_num = 0;
	nodes[nodenum].lchild = nodes[nodenum].rchild = -1;
	strcpy_s(nodes[nodenum].name, name);
	UpdateTab(name, nodenum);
	return nodenum++;
}

int SearchIndex(char* name) {
	unsigned int hash = Hash(name);
	for (int i = 0; i < tabnum; i++)
		if(nodetab[i].hash == hash)
			if (strcmp(nodetab[i].name, name) == 0)
				return nodetab[i].index;
	return NewNode(name, -1);
}


void AddNode_1(int op, char* op1, char* res) {
	int lchild = SearchIndex(op1);
	int root = NewNode(res, op);
	Link(root, lchild, -1);
}

void AddNode_2(int op, char* op1) {
	int lchild = SearchIndex(op1);
	int root = NewNode("", op);
	Link(root, lchild, -1);
}

void AddNode_3(int op, char* res) {
	int root = NewNode(res, op);
	Link(root, -1, -1);
}

void AddNode_4(int op, char* op1, char* op2, char* res) {
	int lchild = SearchIndex(op1);
	int rchild = SearchIndex(op2);
	for(int i = nodenum - 1; i >= 0; i--)
		if(nodes[i].op == op)
			if (nodes[i].lchild == lchild && nodes[i].rchild == rchild) {
				UpdateTab(res, i);
				return;
			}
	int root = NewNode(res, op);
	Link(root, lchild, rchild);
}

void AddNode_5(int op, char* op1, char* op2, char* res) {
	int lchild = SearchIndex(op1);
	int rchild = SearchIndex(op2);
	for (int i = nodenum - 1; i >= 0; i--)
		if (nodes[i].op == op) {
			if (nodes[i].lchild == lchild && nodes[i].rchild == rchild) {
				UpdateTab(res, i);
				return;
			}
			if (nodes[i].lchild == rchild && nodes[i].rchild == lchild) {
				UpdateTab(res, i);
				return;
			}
		}
	int root = NewNode(res, op);
	Link(root, lchild, rchild);
}

void AddNode_6(int op, char* op1, char* op2, char* res) {
	int lchild = SearchIndex(op1);
	int rchild = SearchIndex(op2);
	int root = NewNode(res, op);
	Link(root, lchild, rchild);
}

void AddNode_7(int op) {
	int root = NewNode("", op);
}

void InitDAG() {
	tabnum = nodenum = 0;
}

void InsertDAG(Quadruple code) {
	switch (code.op) {
	case ASN:
		AddNode_1(code.op, code.op1, code.res);
		break;
	case VAL:
	case PRINTS:
	case PRINTI:
	case PRINTC:
		AddNode_2(code.op, code.op1);
		break;
	case SCAN:
		AddNode_3(code.op, code.res);
		break;
	case LARR:
	case LES:
	case LEQ:
	case GTR:
	case GEQ:
	case MINUS:
	case DIVIDE:
	case JZ:
	case JNZ:
		AddNode_4(code.op, code.op1, code.op2, code.res);
		break;
	case PLUS:
	case TIMES:
	case EQU:
	case NEQ:
		AddNode_5(code.op, code.op1, code.op2, code.res);
		break;
	case SARR:
		AddNode_6(code.op, code.op1, code.op2, code.res);
		break;
	case CALL:
		char temp[IdentityMaxLen];
		strcpy_s(temp, code.op1);
		strcat_s(temp, "@");
		if (strcmp(code.res, "") == 0)
			AddNode_2(code.op, temp);
		else
			AddNode_1(code.op, temp, code.res);
		break;
	case RET:
		if (strcmp(code.op1, "") == 0)
			AddNode_7(code.op);
		else
			AddNode_2(code.op, code.op1);
		break;
	}
}

void ExportDAG() {
	int stack[LocalSize];
	int top = -1;
	for (int i = 0; i < nodenum; i++)
		if (nodes[i].op == ASN) {
			int lchild = nodes[i].lchild;
			if (nodes[lchild].op >= 0 && nodes[lchild].parent_num == 1 && nodes[lchild].name[0] == '$') {
				nodes[i].op = nodes[lchild].op;
				nodes[i].lchild = nodes[lchild].lchild;
				nodes[i].rchild = nodes[lchild].rchild;
				nodes[lchild].op = -1;
			}
		}
	for (int i = nodenum - 1; i >= 0; i--)
		if (nodes[i].parent_num == 0) {
			int p = i;
			do{
				stack[++top] = p;
				if (nodes[p].lchild >= 0)
					nodes[nodes[p].lchild].parent_num--;
				if (nodes[p].rchild >= 0)
					nodes[nodes[p].rchild].parent_num--;
				nodes[p].parent_num = -1;
				p = nodes[p].lchild;
			} while (p >= 0 && nodes[p].parent_num == 0 && isSimpleArithmetic(nodes[p].op));
		}
	for (int i = top; i >= 0; i--) {
		int p = stack[i];
		if (nodes[p].op >= 0) {
			switch (nodes[p].op) {
			case CALL:
				char temp[IdentityMaxLen];
				strncpy_s(temp, nodes[nodes[p].lchild].name, strlen(nodes[nodes[p].lchild].name) - 1);
				GenerateTempCode(nodes[p].op, temp, "", nodes[p].name);
				break;
			case ASN:
				GenerateTempCode(nodes[p].op, nodes[nodes[p].lchild].name, "", nodes[p].name);
				break;
			case VAL:
			case PRINTS:
			case PRINTI:
			case PRINTC:
				GenerateTempCode(nodes[p].op, nodes[nodes[p].lchild].name, "", "");
				break;
			case SCAN:
				GenerateTempCode(nodes[p].op, "", "", nodes[p].name);
				break;
			case LARR:
			case SARR:
			case LES:
			case LEQ:
			case GTR:
			case GEQ:
			case MINUS:
			case DIVIDE:
			case PLUS:
			case TIMES:
			case EQU:
			case NEQ:
			case JZ:
			case JNZ:
				GenerateTempCode(nodes[p].op, nodes[nodes[p].lchild].name, nodes[nodes[p].rchild].name, nodes[p].name);
				break;
			case RET:
				if(nodes[p].lchild >= 0)
					GenerateTempCode(nodes[p].op, nodes[nodes[p].lchild].name, "", "");
				else
					GenerateTempCode(nodes[p].op, "", "", "");
				break;
			}
		}
	}
}

bool isSimpleArithmetic(int op) {
	switch (op) {
	case ASN:
	case PLUS:
	case TIMES:
	case MINUS:
	case DIVIDE:
	case EQU:
	case NEQ:
	case LES:
	case LEQ:
	case GTR:
	case GEQ:
		return true;
	}
	return false;
}