#include "stdafx.h"

extern Quadruple midcode[CodeMaxNum];
extern int cnt;
extern Identity* current;
extern Identity global[GlobalSize];
extern Identity local[LocalSize];
extern char name[IdentityMaxLen];
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
			if (midcode[j].op == JZ || midcode[j].op == JNZ || midcode[j].op == J || midcode[j].op == RET) {
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
				for (int k = 0; k < cnt; k++) {
					if (midcode[k].op == JZ || midcode[k].op == JNZ)
						if (strcmp(midcode[k].op2, midcode[j].op1) == 0)
							strcpy_s(midcode[k].op2, midcode[i].op1);
					if (midcode[k].op == J)
						if (strcmp(midcode[k].op1, midcode[j].op1) == 0)
							strcpy_s(midcode[k].op1, midcode[i].op1);
				}
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
			if (midcode[j].op == CALL)
				cnt = 0;
			Identity *ident;
			ident = Search(midcode[j].res, 1);
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

void ConstantCombination() {
	for (int i = 0; i < cnt; i++)
		switch (midcode[i].op) {
		case PROC:
		case FUNC:
			current = Search(midcode[i].res, 2);
			break;
		case PLUS:
		case MINUS:
		case TIMES:
		case DIVIDE:
		case EQU:
		case LES:
		case GTR:
		case LEQ:
		case GEQ:
		case NEQ:
			Identity* ident1 = Search(midcode[i].op1, 3);
			Identity* ident2 = Search(midcode[i].op2, 3);
			Identity* ident = Search(midcode[i].res, 3);
			if (ident1->kind == CONSTANT && ident2->kind == CONSTANT && ident->name[0] == '$') {
				ident->kind = CONSTANT;
				ident->value = Calc(midcode[i].op, ident1->value, ident2->value);
				midcode[i].op = DEL;
			}
			break;
		}
}

void ClearUnusedVar() {
	for(int i = 0; i < cnt; i++)
		switch (midcode[i].op) {
		case PARA:
		case VAL:
		case CALL:
		case LARR:
		case SARR:
		case JZ:
		case JNZ:
		case SCAN:
		case PRINTI:
		case PRINTC:
		case RET:
		case PLUS:
		case MINUS:
		case TIMES:
		case DIVIDE:
		case EQU:
		case LES:
		case LEQ:
		case GTR:
		case GEQ:
		case NEQ:
		case ASN:
			Identity* ident1 = Search(midcode[i].op1, 3);
			Identity* ident2 = Search(midcode[i].op2, 3);
			Identity* ident = Search(midcode[i].res, 3);
			if (ident1 != NULL)
				ident1->isused = true;
			if (ident2 != NULL)
				ident2->isused = true;
			if (ident != NULL)
				ident->isused = true;
			break;
		}
	for(int i = 0; i < gsize; i++)
		if ((global[i].kind == VARIABLE || global[i].kind == ARRAY) && global[i].isused == false) {
			global[i].kind = DELETED;
			strcpy_s(name, global[i].name);
			Warning(UNUSED_IDENTITY_WARNING);
		}
		else if(global[i].kind == PROCEDURE || global[i].kind == FUNCTION)
			for(int j = global[i].l; j < global[i].r; j++)
				if ((local[j].kind == VARIABLE || local[j].kind == ARRAY) && local[j].isused == false) {
					local[j].kind == DELETED;
					if (local[j].name[0] != '$') {
						strcpy_s(name, local[j].name);
						Warning(UNUSED_IDENTITY_WARNING);
					}
				}
}

int Calc(int op, int op1, int op2) {
	switch (op) {
	case PLUS:   return op1 + op2;
	case MINUS:  return op1 - op2;
	case TIMES:  return op1 * op2;
	case DIVIDE: return op1 / op2;
	case EQU:    return op1 == op2 ? 1 : 0;
	case LES:    return op1 < op2 ? 1 : 0;
	case GTR:    return op1 > op2 ? 1 : 0;
	case LEQ:    return op1 <= op2 ? 1 : 0;
	case GEQ:    return op1 >= op2 ? 1 : 0;
	case NEQ:    return op1 != op2 ? 1 : 0;
	}
	return 0;
}