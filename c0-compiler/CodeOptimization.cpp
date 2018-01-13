#include "stdafx.h"

extern Quadruple midcode[CodeMaxNum];
extern int cnt;
extern Identity* current;
extern Identity global[GlobalSize];
extern Identity local[LocalSize];
extern int gsize;
extern int lsize;

Quadruple tempcode[CodeMaxNum];
int temp_cnt;

BaseBlock block[CodeMaxNum];
int block_num;

void GetBaseBlock() {
	block_num = 0;
	int i = 0;
	while (i < cnt) {
		int j = i + 1;
		while (j < cnt) {
			if (midcode[j].op == PROC || midcode[j].op == FUNC || midcode[j].op == LABEL)
				break;
			if (midcode[j].op == JZ || midcode[j].op == JNZ || midcode[j].op == RET) {
				j++;
				break;
			}
			j++;
		}
		block[block_num].s = i;
		block[block_num++].t = j;
		i = j;
	}
}

void CopyToTemp(Quadruple code) {
	tempcode[temp_cnt].op = code.op;
	strcpy_s(tempcode[temp_cnt].op1, code.op1);
	strcpy_s(tempcode[temp_cnt].op2, code.op2);
	strcpy_s(tempcode[temp_cnt].res, code.res);
	temp_cnt++;
}

void CopyToMid(Quadruple code) {
	midcode[cnt].op = code.op;
	strcpy_s(midcode[cnt].op1, code.op1);
	strcpy_s(midcode[cnt].op2, code.op2);
	strcpy_s(midcode[cnt].res, code.res);
	cnt++;
}

void DeleteInvalidCode() {
	for (int i = 0; i < cnt; i++)
		if (midcode[i].op == LABEL) {
			int j = i + 1;
			while (j < cnt && midcode[j].op == LABEL) {
				midcode[j].op = DEL;
				for (int k = 0; k < cnt; k++)
					if (midcode[k].op == JZ || midcode[k].op == JNZ)
						if (strcmp(midcode[k].op2, midcode[j].op1) == 0)
							strcpy_s(midcode[k].op2, midcode[i].op1);
				j++;
			}
		}
		else if (midcode[i].op == RET) {
			int j = i + 1;
			while (j < cnt) {
				if (midcode[j].op == LABEL)
					break;
				if (midcode[j].op == PROC)
					break;
				if (midcode[j].op == FUNC)
					break;
				midcode[j++].op = DEL;
			}
		}
}

void CommonSubexpressionElimination() {
	temp_cnt = 0;
	GetBaseBlock();
	for (int i = 0; i < block_num; i++) {
		for (int j = block[i].s; j < block[i].t; j++)
			switch (midcode[j].op) {
			case CONST:
			case VAR:
			case ARR:
			case PROC:
			case FUNC:
			case PARA:
			case LABEL:	
				CopyToTemp(midcode[j]);
				break;
			default:
				InsertDAG(midcode[j]);
			}
		ExportDAG();
		InitDAG();
	}
	cnt = 0;
	for (int i = 0; i < temp_cnt; i++)
		CopyToMid(tempcode[i]);
}

void AllocGlobalReg() {
	for (int i = 0; i < gsize; i++)
		if (global[i].kind == PROCEDURE || global[i].kind == FUNCTION) {
			int pos[LocalSize];
			int cnt = 0;
			for (int j = global[i].l; j < global[i].r; j++)
				if ((local[j].kind == VARIABLE || local[j].kind == PARAMETER) && local[j].name[0] != '$')
					pos[cnt++] = j;
			for (int j = 0; j < cnt && j < 8; j++) {
				int max = j;
				for (int k = j + 1; k < cnt; k++)
					if (local[pos[k]].weight > local[pos[max]].weight)
						max = k;
				local[pos[max]].reg = s0 + j;
				pos[max] = pos[j];
			}
		}
}

void AllocTempReg() {
	GetBaseBlock();
	for (int i = 0; i < block_num; i++) {
		Identity* pos[LocalSize];
		int cnt = 0;
		for (int j = block[i].s; j < block[i].t; j++) {
			if (midcode[j].op == PROC || midcode[j].op == FUNC)
				current = Search(midcode[j].res, 2);
			Identity *ident1, *ident2, *ident;
			ident1 = Search(midcode[j].op1, 1);
			ident2 = Search(midcode[j].op2, 1);
			ident = Search(midcode[j].res, 1);
			if (ident1 != NULL)
				if (ident1->kind == VARIABLE && ident1->name[0] == '$') {
					bool exist = false;
					for (int k = 0; k < cnt; k++)
						if (pos[k] == ident1) {
							exist = true;
							break;
						}
					if (!exist)
						pos[cnt++] = ident1;
				}
			if (ident2 != NULL)
				if (ident2->kind == VARIABLE && ident2->name[0] == '$') {
					bool exist = false;
					for (int k = 0; k < cnt; k++)
						if (pos[k] == ident2) {
							exist = true;
							break;
						}
					if (!exist)
						pos[cnt++] = ident2;
				}
			if (ident != NULL)
				if (ident->kind == VARIABLE && ident->name[0] == '$') {
					bool exist = false;
					for (int k = 0; k < cnt; k++)
						if (pos[k] == ident) {
							exist = true;
							break;
						}
					if (!exist)
						pos[cnt++] = ident;
				}
		}
		for (int j = 0; j < cnt && j < 11; j++) {
			int max = j;
			for (int k = j + 1; k < cnt; k++)
				if (pos[k]->weight > pos[max]->weight)
					max = k;
			pos[max]->reg = a1 + j;
			pos[max] = pos[j];
		}
	}
}