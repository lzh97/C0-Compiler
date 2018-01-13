#include "stdafx.h"

extern FILE* targetcode;

extern Quadruple midcode[CodeMaxNum];
extern int cnt;
extern Identity global[GlobalSize];
extern Identity local[LocalSize];
extern Identity* current;
extern int gsize;

int offset;
int top = 0;
int str = 0;
char res[10];

int Calc(int op, int op1, int op2);

void AllocGlobal(Identity* ident, char* name, char* value);
void AllocLocal(Identity *&ident);
void PopPara(Identity ident);
void PushPara(Identity ident);
char* StringLabel(int str);

void MIPS_LABEL(char* label);
void MIPS_JAL(char* label);
void MIPS_J(char* label);
void MIPS_JR(int rs);
void MIPS_LA(int rt, char* l);
void MIPS_LI(int rt, int value);
void MIPS_LW(int rt, int rs, int offset);
void MIPS_SW(int rt, int rs, int offset);
void MIPS_MOVE(int rt, int rs);
void MIPS_ADD(int rd, int rs, int rt);
void MIPS_ADDI(int rt, int rs, int value);
void MIPS_SUB(int rd, int rs, int rt);
void MIPS_SUBI(int rt, int rs, int value);
void MIPS_MUL(int rd, int rs, int rt);
void MIPS_DIV(int rt, int rs);
void MIPS_MFLO(int rs);
void MIPS_BEQ(int rt, int rs, char* label);
void MIPS_BNE(int rt, int rs, char* label);
void MIPS_SLT(int rd, int rs, int rt);
void MIPS_SLE(int rd, int rs, int rt);
void MIPS_SGT(int rd, int rs, int rt);
void MIPS_SGE(int rd, int rs, int rt);
void MIPS_SEQ(int rd, int rs, int rt);
void MIPS_SNE(int rd, int rs, int rt);
void MIPS_SYSCALL();

void GenerateMIPS32() {
	Identity *ident, *ident1, *ident2;
	fprintf(targetcode, ".data\n");
	for (int i = 0; i < gsize; i++) {	//全局变量分配
		ident = &global[i];
		AllocGlobal(ident, NULL, NULL);
	}
	for(int i = 0; i < cnt; i++)	//字符串常量分配
		if (midcode[i].op == PRINTS) {
			AllocGlobal(NULL, StringLabel(str), midcode[i].op1);
			strcpy_s(midcode[i].op1, StringLabel(str++));
		}
	fprintf(targetcode, ".text\n");
	MIPS_JAL("main");
	MIPS_LI(v0, 10);
	MIPS_SYSCALL();
	for (int i = 0; i < cnt; i++)
		switch (midcode[i].op) {
		case PROC:
		case FUNC:
			top = offset = 0;
			current = Search(midcode[i].res, 2);
			MIPS_LABEL(midcode[i].res);
			MIPS_SUBI(gp, gp, current->size * DATASIZE);
			MIPS_SW(fp, sp, -offset++ * DATASIZE);		//保存退栈信息
			MIPS_SW(ra, sp, -offset++ * DATASIZE);
			offset += s7 - s0 + 1;		//全局寄存器分配
			for (int j = current->l; j < current->r; j++) {	//局部变量分配
				ident = &local[j];
				AllocLocal(ident);
			}
			break;
		case PARA:
			ident = Search(midcode[i].res, 1);
			PopPara(*ident);
			break;
		case LABEL:
			MIPS_LABEL(midcode[i].op1);
			break;
		case VAL:
			ident1 = Search(midcode[i].op1, 3);
			PushPara(*ident1);
			break;
		case CALL:
			ident1 = Search(midcode[i].op1, 2);
			ident = Search(midcode[i].res, 3);
			for (int offset = 2; offset < 10; offset++)		//保存全局寄存器
				MIPS_SW(s0 + offset - 2, sp, -offset * DATASIZE);
			MIPS_MOVE(fp, sp);
			MIPS_SUBI(sp, sp, offset * DATASIZE);		//压栈
			MIPS_JAL(midcode[i].op1);
			if (ident != NULL) {
				if (ident->reg >= 0)
					MIPS_MOVE(ident->reg, v0);
				else
					MIPS_SW(v0, sp, ident->addr);
			}
			break;
		case LARR:
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1->isglobal)		//基地址
				MIPS_LA(t8, ident1->name);
			else if (ident1->reg >= 0)
				MIPS_MOVE(t8, ident1->reg);
			else
				MIPS_ADDI(t8, sp, ident1->addr);
			if (ident2->kind == CONSTANT)		//偏移量
				MIPS_LI(t9, ident2->value);
			else if (ident2->isglobal) {
				MIPS_LA(t9, ident2->name);
				MIPS_LW(t9, t9, 0);
			}
			else if (ident2->reg >= 0)
				MIPS_MOVE(t9, ident2->reg);
			else
				MIPS_LW(t9, sp, ident2->addr);
			MIPS_LI(at, 4);		//数组元素地址
			MIPS_MUL(t9, t9, at);
			if (ident1->isglobal)
				MIPS_ADD(t8, t8, t9);
			else
				MIPS_SUB(t8, t8, t9);
			MIPS_LW(t8, t8, 0);		//数组元素
			if (ident->isglobal) {		//取数组元素
				MIPS_LA(t9, ident->name);
				MIPS_SW(t8, t9, 0);
			}
			else if (ident->reg >= 0)
				MIPS_MOVE(ident->reg, t8);
			else {
				MIPS_ADDI(t9, sp, ident->addr);
				MIPS_SW(t8, t9, 0);
			}
			break;
		case SARR:
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			ident = Search(midcode[i].res, 3);
			if (ident->isglobal)		//基地址
				MIPS_LA(t8, ident->name);
			else if (ident->reg >= 0)
				MIPS_MOVE(t8, ident->reg);
			else
				MIPS_ADDI(t8, sp, ident->addr);
			if (ident2->kind == CONSTANT)		//偏移量
				MIPS_LI(t9, ident2->value);
			else if (ident2->isglobal) {
				MIPS_LA(t9, ident2->name);
				MIPS_LW(t9, t9, 0);
			}
			else if (ident2->reg >= 0)
				MIPS_MOVE(t9, ident2->reg);
			else
				MIPS_LW(t9, sp, ident2->addr);
			MIPS_LI(at, 4);		//数组元素地址
			MIPS_MUL(t9, t9, at);
			if (ident->isglobal)
				MIPS_ADD(t8, t8, t9);
			else
				MIPS_SUB(t8, t8, t9);
			if (ident1->kind == CONSTANT)		//元素
				MIPS_LI(t9, ident1->value);
			else if (ident1->isglobal) {
				MIPS_LA(t9, ident1->name);
				MIPS_LW(t9, t9, 0);
			}
			else if (ident1->reg >= 0)
				MIPS_MOVE(t9, ident1->reg);
			else
				MIPS_LW(t9, sp, ident1->addr);
			MIPS_SW(t9, t8, 0);		//存元素
			break;
		case JZ:
		case JNZ:
			ident1 = Search(midcode[i].op1, 3);
			if (ident1->kind == CONSTANT)		//取元素
				MIPS_LI(t8, ident1->value);
			else if (ident1->isglobal) {
				MIPS_LA(t8, ident1->name);
				MIPS_LW(t8, t8, 0);
			}
			else if (ident1->reg >= 0)
				MIPS_MOVE(t8, ident1->reg);
			else
				MIPS_LW(t8, sp, ident1->addr);
			if (midcode[i].op == JZ)		//条件跳转
				MIPS_BEQ(t8, 0, midcode[i].op2);
			else
				MIPS_BNE(t8, 0, midcode[i].op2);
			break;
		case SCAN:
			ident = Search(midcode[i].res, 3);
			if (ident->type == INT)		//系统调用
				MIPS_LI(v0, 5);
			else
				MIPS_LI(v0, 12);
			MIPS_SYSCALL();
			if (ident->isglobal) {		//存元素
				MIPS_LA(t8, ident->name);
				MIPS_SW(v0, t8, 0);
			}
			else if (ident->reg >= 0)
				MIPS_MOVE(ident->reg, v0);
			else
				MIPS_SW(v0, sp, ident->addr);
			break;
		case PRINTS:
			MIPS_LA(a0, midcode[i].op1);
			MIPS_LI(v0, 4);
			MIPS_SYSCALL();
			break;
		case PRINTI:
		case PRINTC:
			ident1 = Search(midcode[i].op1, 3);
			if (ident1->kind == CONSTANT)		//取元素
				MIPS_LI(a0, ident1->value);
			else if (ident1->isglobal) {
				MIPS_LA(a0, ident1->name);
				MIPS_LW(a0, a0, 0);
			}
			else if (ident1->reg >= 0)
				MIPS_MOVE(a0, ident1->reg);
			else
				MIPS_LW(a0, sp, ident1->addr);
			if (midcode[i].op == PRINTI)
				MIPS_LI(v0, 1);
			else
				MIPS_LI(v0, 11);
			MIPS_SYSCALL();
			break;
		case RET:
			ident1 = Search(midcode[i].op1, 3);
			if (ident1 != NULL)		//返回值
				if (ident1->kind == CONSTANT)
					MIPS_LI(v0, ident1->value);
				else if (ident1->isglobal) {
					MIPS_LA(v0, ident->name);
					MIPS_LW(v0, v0, 0);
				}
				else if (ident1->reg >= 0)
					MIPS_MOVE(v0, ident1->reg);
				else
					MIPS_LW(v0, sp, ident->addr);
			MIPS_LW(ra, sp, -4);		//退栈
			MIPS_LW(sp, sp, 0);
			for (int offset = 2; offset < 10; offset++)		//恢复全局寄存器
				MIPS_LW(s0 + offset - 2, sp, -offset * DATASIZE);
			MIPS_JR(ra);
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
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1->kind == CONSTANT && ident2->kind == CONSTANT) {		//常数合并
				if (ident->isglobal) {
					MIPS_LA(t8, ident->name);
					MIPS_LI(t9, Calc(midcode[i].op, ident1->value, ident2->value));
					MIPS_SW(t9, t8, 0);
				}
				else if (ident->reg >= 0)
					MIPS_LI(ident->reg, Calc(midcode[i].op, ident1->value, ident2->value));
				else {
					MIPS_LI(t9, Calc(midcode[i].op, ident1->value, ident2->value));
					MIPS_SW(t9, sp, ident->addr);
				}
			}
			else {
				if (ident1->kind == CONSTANT)		//取元素
					MIPS_LI(t8, ident1->value);
				else if (ident1->isglobal) {
					MIPS_LA(t8, ident1->name);
					MIPS_LW(t8, t8, 0);
				}
				else if (ident1->reg >= 0)
					MIPS_MOVE(t8, ident1->reg);
				else
					MIPS_LW(t8, sp, ident1->addr);
				if (ident2->kind == CONSTANT)		//取元素
					MIPS_LI(t9, ident2->value);
				else if (ident2->isglobal) {
					MIPS_LA(t9, ident2->name);
					MIPS_LW(t9, t9, 0);
				}
				else if (ident2->reg >= 0)
					MIPS_MOVE(t9, ident2->reg);
				else
					MIPS_LW(t9, sp, ident2->addr);
				switch (midcode[i].op) {		//运算
				case PLUS:
					MIPS_ADD(t8, t8, t9);
					break;
				case MINUS:
					MIPS_SUB(t8, t8, t9);
					break;
				case TIMES:
					MIPS_MUL(t8, t8, t9);
					break;
				case DIVIDE:
					MIPS_DIV(t8, t9);
					MIPS_MFLO(t8);
					break;
				case EQU:
					MIPS_SEQ(t8, t8, t9);
					break;
				case LES:
					MIPS_SLT(t8, t8, t9);
					break;
				case GTR:
					MIPS_SGT(t8, t8, t9);
					break;
				case LEQ:
					MIPS_SLE(t8, t8, t9);
					break;
				case GEQ:
					MIPS_SGE(t8, t8, t9);
					break;
				case NEQ:
					MIPS_SNE(t8, t8, t9);
					break;
				}
				if (ident->isglobal) {		//存元素		
					MIPS_LA(t9, ident->name);
					MIPS_SW(t8, t9, 0);
				}
				else if (ident->reg >= 0)
					MIPS_MOVE(ident->reg, t8);
				else
					MIPS_SW(t8, sp, ident->addr);
			}
			break;
		case ASN:
			ident1 = Search(midcode[i].op1, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1->kind == CONSTANT)		//取元素
				MIPS_LI(t8, ident1->value);
			else if (ident1->isglobal) {
				MIPS_LA(t8, ident1->name);
				MIPS_LW(t8, t8, 0);
			}
			else if (ident1->reg >= 0)
				MIPS_MOVE(t8, ident1->reg);
			else
				MIPS_LW(t8, sp, ident1->addr);
			if (ident->isglobal) {		//存元素
				MIPS_LA(t9, ident->name);
				MIPS_SW(t8, t9, 0);
			}
			else if (ident->reg >= 0)
				MIPS_MOVE(ident->reg, t8);
			else
				MIPS_SW(t8, sp, ident->addr);
			break;
		}
}

void AllocGlobal(Identity* ident, char* name, char* value) {
	if (ident == NULL)
		fprintf(targetcode, "%s: .asciiz %s\n", name, value);
	else {
		if (ident->kind == ARRAY) 
			fprintf(targetcode, "%s: .space %d\n", ident->name, ident->size * DATASIZE);
		else if(ident->kind == VARIABLE)
			fprintf(targetcode, "%s: .word %d\n", ident->name, ident->value);
	}
}
void AllocLocal(Identity *&ident) {
	if (!ident->isused)
		return;
	if (ident->kind == CONSTANT)
		return;
	if (ident->reg >= 0)
		return;
	ident->addr = -offset * DATASIZE;
	if (ident->kind == ARRAY)
		offset += ident->size;
	else
		offset++;
}
void PopPara(Identity ident) {
	if (ident.reg >= 0)
		MIPS_LW(ident.reg, gp, top++ * DATASIZE);
	else {
		MIPS_LW(t8, gp, top++ * DATASIZE);
		MIPS_SW(t8, sp, ident.addr);
	}
}
void PushPara(Identity ident) {
	if (ident.kind == CONSTANT) {
		MIPS_LI(t8, ident.value);
		MIPS_SW(t8, gp, 0);
	}
	else if (ident.isglobal) {
		MIPS_LA(t8, ident.name);
		MIPS_LW(t9, t8, 0);
		MIPS_SW(t9, gp, 0);
	}
	else if(ident.reg >= 0)
		MIPS_SW(ident.reg, gp, 0);
	else {
		MIPS_LW(t8, sp, ident.addr);
		MIPS_SW(t8, gp, 0);
	}
	MIPS_ADDI(gp, gp, 4);
}
char* StringLabel(int str) {
	char tmp[10];
	strcpy_s(res, "$str");
	_itoa_s(str, tmp, 10);
	strcat_s(res, tmp);
	return res;
}

void MIPS_LABEL(char* label) {
	fprintf(targetcode, "%s:\n", label);
}
void MIPS_JAL(char* label) { 
	fprintf(targetcode, "\t jal  %s\n", label); 
}
void MIPS_J(char* label) {
	fprintf(targetcode, "\t j    %s\n", label);
}
void MIPS_JR(int rs) {
	fprintf(targetcode, "\t jr   %s\n", reg[rs]);
}
void MIPS_LA(int rt, char* label) {
	fprintf(targetcode, "\t la   %s, %s\n", reg[rt], label);
}
void MIPS_LI(int rt, int value) {
	fprintf(targetcode, "\t li   %s, %d\n", reg[rt], value);
}
void MIPS_LW(int rt, int rs, int offset) {
	fprintf(targetcode, "\t lw   %s, %d(%s)\n", reg[rt], offset, reg[rs]);
}
void MIPS_SW(int rt, int rs, int offset) {
	fprintf(targetcode, "\t sw   %s, %d(%s)\n", reg[rt], offset, reg[rs]);
}
void MIPS_MOVE(int rt, int rs) {
	fprintf(targetcode, "\t move %s, %s\n", reg[rt], reg[rs]);
}
void MIPS_ADD(int rd, int rs, int rt) {
	fprintf(targetcode, "\t add  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_ADDI(int rt, int rs, int value) {
	fprintf(targetcode, "\t addi %s, %s, %d\n", reg[rt], reg[rs], value);
}
void MIPS_SUB(int rd, int rs, int rt) {
	fprintf(targetcode, "\t sub  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SUBI(int rt, int rs, int value) {
	fprintf(targetcode, "\t subi %s, %s, %d\n", reg[rt], reg[rs], value);
}
void MIPS_MUL(int rd, int rs, int rt) {
	fprintf(targetcode, "\t mul  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_DIV(int rt, int rs) {
	fprintf(targetcode, "\t div  %s, %s\n", reg[rt], reg[rs]);
}
void MIPS_MFLO(int rs) {
	fprintf(targetcode, "\t mflo %s\n", reg[rs]);
}
void MIPS_BEQ(int rt, int rs, char* label) {
	fprintf(targetcode, "\t beq  %s, %s, %s\n", reg[rt], reg[rs], label);
}
void MIPS_BNE(int rt, int rs, char* label) {
	fprintf(targetcode, "\t bne  %s, %s, %s\n", reg[rt], reg[rs], label);
}
void MIPS_SLT(int rd, int rs, int rt) {
	fprintf(targetcode, "\t slt  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SLE(int rd, int rs, int rt) {
	fprintf(targetcode, "\t sle  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SGT(int rd, int rs, int rt) {
	fprintf(targetcode, "\t sgt  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SGE(int rd, int rs, int rt) {
	fprintf(targetcode, "\t sge  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SEQ(int rd, int rs, int rt) {
	fprintf(targetcode, "\t seq  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SNE(int rd, int rs, int rt) {
	fprintf(targetcode, "\t sne  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SYSCALL() {
	fprintf(targetcode, "\t syscall\n");
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