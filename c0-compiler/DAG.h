#pragma once
#include "stdafx.h"

struct Node{
	int parent_num;
	int op;
	int lchild, rchild;
	char name[IdentityMaxLen];
};

struct NodeInfo {
	char name[IdentityMaxLen];
	unsigned int hash;
	int index;
};

void InitDAG();
void InsertDAG(Quadruple code);
void ExportDAG();