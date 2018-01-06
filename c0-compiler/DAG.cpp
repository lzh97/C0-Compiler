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
	for(int i = nodenum - 1; i >= 0; i--)
		if (nodes[i].op == op)
			if (nodes[i].lchild == lchild) {
				UpdateTab(res, i);
				return;
			}
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
	}
}

void ExportDAG() {
	int stack[LocalSize];
	int top = -1;
	for (int i = nodenum - 1; i >= 0; i--)
		if (nodes[i].parent_num == 0) {
			int p = i;
			while (p >= 0 && nodes[p].parent_num == 0) {
				if (nodes[p].op == LARR) {
					bool cancel = false;
					for (int j = p + 1; j < nodenum; j++)
						if (nodes[j].parent_num == 0 && nodes[j].op == SARR && strcmp(nodes[nodes[p].lchild].name, nodes[j].name) == 0) {
							cancel = true;
							break;
						}
					if (cancel)
						break;
				}
				if (nodes[p].op == SARR) {
					bool cancel = false;
					for (int j = p + 1; j < nodenum; j++)
						if (nodes[j].parent_num == 0 && nodes[j].op == LARR && strcmp(nodes[p].name, nodes[nodes[j].lchild].name) == 0) {
							cancel = true;
							break;
						}
					if (cancel)
						break;
				}
				if (nodes[p].op == SCAN) {
					bool cancel = false;
					for(int j = p + 1; j < nodenum; j++)
						if (nodes[j].parent_num == 0 && nodes[j].op == SCAN) {
							cancel = true;
							break;
						}
					if (cancel)
						break;
				}
				stack[++top] = p;
				if (nodes[p].lchild >= 0)
					nodes[nodes[p].lchild].parent_num--;
				if (nodes[p].rchild >= 0)
					nodes[nodes[p].rchild].parent_num--;
				nodes[p].parent_num = -1;
				p = nodes[p].lchild;
			}
		}
	for (int i = top; i >= 0; i--) {
		int p = stack[i];
		if (nodes[p].op >= 0) {
			switch (nodes[p].op) {
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
				GenerateTempCode(nodes[p].op, nodes[nodes[p].lchild].name, nodes[nodes[p].rchild].name, nodes[p].name);
				break;
			}
			int index = SearchIndex(nodes[p].name);
			for (int i = 0; i < tabnum; i++)
				if (nodetab[i].index == index && strcmp(nodetab[i].name, nodes[p].name) != 0)
					GenerateTempCode(ASN, nodes[p].name, "", nodetab[i].name);
		}
	}
}