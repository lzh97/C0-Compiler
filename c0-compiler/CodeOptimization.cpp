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

int Calc(int op, int op1, int op2);

void GetBaseBlock() {
	block_num = 0;
	int i = 0;
	while (i < cnt) {
		int j = i + 1;
		while (j < cnt) {
			if (midcode[j].op == PROC)
				break;
			if (midcode[j].op == FUNC)
				break;
			if (midcode[j].op == LABEL)
				break;
			if (midcode[j].op == CALL)
				break;
			if (midcode[j].op == JZ)
				break;
			if (midcode[j].op == JNZ)
				break;
			if (midcode[j].op == RET)
				break;
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
			case CALL:
			case JZ:
			case JNZ:
			case RET:
				ExportDAG();
				InitDAG();
				CopyToTemp(midcode[j]);
				break;
			default:
				InsertDAG(midcode[j]);
			}
	}
	cnt = 0;
	for (int i = 0; i < temp_cnt; i++)
		CopyToMid(tempcode[i]);
}

/*void ConstantReplace() {
	Identity *ident1, *ident2, *ident;
	for (int i = 0; i < cnt; i++)
		switch (midcode[i].op) {
		case PROC:
		case FUNC:
			current = Search(midcode[i].res, 2);
			break;
		case VAL:
		case JZ:
		case JNZ:
		case PRINTI:
		case PRINTC:
		case RET:
		case ASN:
			ident1 = Search(midcode[i].op1, 3);
			if (ident1 != NULL)
				if (ident1->kind == CONSTANT)
					strcpy_s(midcode[i].op1, Int2String(ident1->value));
			break;
		case LARR:
			ident2 = Search(midcode[i].op2, 3);
			if (ident2 != NULL)
				if (ident2->kind == CONSTANT)
					strcpy_s(midcode[i].op2, Int2String(ident2->value));
			break;
		case SARR:
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			if (ident1 != NULL)
				if (ident1->kind == CONSTANT)
					strcpy_s(midcode[i].op1, Int2String(ident1->value));
			if (ident2 != NULL)
				if (ident2->kind == CONSTANT)
					strcpy_s(midcode[i].op2, Int2String(ident2->value));
			break;
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
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1 != NULL && ident2 != NULL) {
				if (ident1->kind == CONSTANT && ident2->kind == CONSTANT) {
					midcode[i].op = DEL;
					ident->kind = CONSTANT;
					ident->value = Calc(midcode[i].op, ident1->value, ident2->value);
					break;
				}
			}
			if (ident1 != NULL)
				if (ident1->kind == CONSTANT)
					strcpy_s(midcode[i].op1, Int2String(ident1->value));
			if (ident2 != NULL)
				if (ident2->kind == CONSTANT)
					strcpy_s(midcode[i].op2, Int2String(ident2->value));
			break;
		}
	for (int i = 0; i < gsize; i++)
		if (global[i].kind == CONSTANT)
			global[i].kind = DELETED;
	for (int i = 0; i < lsize; i++)
		if (local[i].kind == CONSTANT)
			local[i].kind = DELETED;
}*/

int Calc(int op, int op1, int op2) {
	switch (op) {
	case PLUS:return op1 + op2;
	case MINUS:return op1 - op2;
	case TIMES:return op1 * op2;
	case DIVIDE:return op1 / op2;
	case EQU:return op1 == op2 ? 1 : 0;
	case LES:return op1 < op2 ? 1 : 0;
	case LEQ:return op1 <= op2 ? 1 : 0;
	case GTR:return op1 > op2 ? 1 : 0;
	case GEQ:return op1 >= op2 ? 1 : 0;
	case NEQ:return op1 != op2 ? 1 : 0;
	}
	return 0;
}