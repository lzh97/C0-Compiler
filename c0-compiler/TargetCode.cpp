#include "stdafx.h"

extern FILE* targetcode;

extern Quadruple midcode[CodeMaxNum];
extern int cnt;
extern Identity local[LocalSize];
extern Identity* current;

int offset;
int top = 0;
int str = 0;
char res[10];

void AllocGlobal(Identity* ident, char* name, char* value);
void AllocLocal(Identity *&ident);
void PopPara(Identity ident);
void PushPara(Identity* ident, int value);
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
	int value = 95;
	fprintf(targetcode, ".data\n");
	int i = 0;
	for (; i < cnt; i++) {		//全局变量、常量分配
		if (midcode[i].op == FUNC || midcode[i].op == PROC)
			break;
		ident = Search(midcode[i].res, 2);
		AllocGlobal(ident, "", "");				
	}
	for(int j = 0; j < cnt; j++)	//字符串常量分配
		if (midcode[j].op == PRINTS) {
			AllocGlobal(NULL, StringLabel(str), midcode[j].op1);
			strcpy_s(midcode[j].op1, StringLabel(str++));
		}
	fprintf(targetcode, ".text\n");
	MIPS_JAL("main");
	MIPS_LI(v0, 10);
	MIPS_SYSCALL();
	for (; i < cnt; i++)
		switch (midcode[i].op) {
		case CONST:
		case VAR:
		case ARR:
			break;
		case PROC:
		case FUNC:
			top = offset = 0;
			current = Search(midcode[i].res, 2);
			MIPS_LABEL(midcode[i].res);
			MIPS_SUBI(gp, gp, current->size * DATASIZE);
			MIPS_SW(fp, sp, -offset++ * DATASIZE);		//保存退栈信息
			MIPS_SW(ra, sp, -offset++ * DATASIZE);
			for (int j = current->l; j < current->r; j++) {
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
			if (ident1 == NULL)
				value = atoi(midcode[i].op1);
			PushPara(ident1, value);
			break;
		case CALL:
			ident1 = Search(midcode[i].op1, 2);
			ident = Search(midcode[i].res, 3);
			MIPS_MOVE(fp, sp);
			MIPS_SUBI(sp, sp, offset * DATASIZE);		//压栈
			MIPS_JAL(midcode[i].op1);
			if (ident != NULL)
				MIPS_SW(v0, sp, ident->addr);
			break;
		case LARR:
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1->isglobal)		//基地址
				MIPS_LA(t0, ident1->name);
			else
				MIPS_ADDI(t0, sp, ident1->addr);
			if (ident2 == NULL) {		//偏移量
				value = atoi(midcode[i].op2);
				MIPS_LI(t1, value * DATASIZE);
			}
			else {
				if (ident2->isglobal) {
					MIPS_LA(t1, ident2->name);
					MIPS_LW(t1, t1, 0);
				}
				else
					MIPS_LW(t1, sp, ident2->addr);
			}
			if (ident->isglobal)
				MIPS_LA(t3, ident->name);
			else
				MIPS_ADDI(t3, sp, ident->addr);
			MIPS_LI(at, 4);
			MIPS_MUL(t1, t1, at);
			if (ident1->isglobal)
				MIPS_ADD(t0, t0, t1);
			else
				MIPS_SUB(t0, t0, t1);
			MIPS_LW(t2, t0, 0);
			MIPS_SW(t2, t3, 0);
			break;
		case SARR:
			ident1 = Search(midcode[i].op1, 3);
			ident2 = Search(midcode[i].op2, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1 == NULL) {
				value = atoi(midcode[i].op1);
				MIPS_LI(t0, value);
			}
			else {
				if (ident1->isglobal) {
					MIPS_LA(t0, ident1->name);
					MIPS_LW(t0, t0, 0);
				}
				else
					MIPS_LW(t0, sp, ident1->addr);
			}
			if (ident2 == NULL) {		//偏移量
				value = atoi(midcode[i].op2);
				MIPS_LI(t1, value);
			}
			else {
				if (ident2->isglobal) {
					MIPS_LA(t1, ident2->name);
					MIPS_LW(t1, t1, 0);
				}
				else
					MIPS_LW(t1, sp, ident2->addr);
			}
			if (ident->isglobal)		//基地址
				MIPS_LA(t2, ident->name);
			else
				MIPS_ADDI(t2, sp, ident->addr);
			MIPS_LI(at, 4);
			MIPS_MUL(t1, t1, at);
			if (ident->isglobal)
				MIPS_ADD(t2, t2, t1);
			else
				MIPS_SUB(t2, t2, t1);
			MIPS_SW(t0, t2, 0);
			break;
		case JZ:
		case JNZ:
			ident1 = Search(midcode[i].op1, 3);
			if (ident1 == NULL) {
				value = atoi(midcode[i].op1);
				MIPS_LI(t0, value);
			}
			else {
				if (ident1->isglobal) {
					MIPS_LA(t0, ident1->name);
					MIPS_LW(t0, t0, 0);
				}
				else
					MIPS_LW(t0, sp, ident1->addr);
			}
			if (midcode[i].op == JZ)
				MIPS_BEQ(t0, 0, midcode[i].op2);
			else
				MIPS_BNE(t0, 0, midcode[i].op2);
			break;
		case SCAN:
			ident = Search(midcode[i].res, 3);
			if (ident->isglobal)
				MIPS_LA(t0, ident->name);
			else
				MIPS_ADDI(t0, sp, ident->addr);
			if (ident->type == INT)
				MIPS_LI(v0, 5);
			else
				MIPS_LI(v0, 12);
			MIPS_SYSCALL();
			MIPS_SW(v0, t0, 0);
			break;
		case PRINTS:
			MIPS_LA(a0, midcode[i].op1);
			MIPS_LI(v0, 4);
			MIPS_SYSCALL();
			break;
		case PRINTI:
		case PRINTC:
			ident1 = Search(midcode[i].op1, 3);
			if (ident1 == NULL) {
				value = atoi(midcode[i].op1);
				MIPS_LI(a0, value);
			}
			else {
				if (ident1->isglobal) {
					MIPS_LA(a0, ident1->name);
					MIPS_LW(a0, a0, 0);
				}
				else
					MIPS_LW(a0, sp, ident1->addr);
			}
			if (ident1->type == INT)
				MIPS_LI(v0, 1);
			else
				MIPS_LI(v0, 11);
			MIPS_SYSCALL();
			break;
		case RET:
			if (strcmp(midcode[i].op1, "") != 0) {
				ident = Search(midcode[i].op1, 3);
				if (ident != NULL)		//返回值
					if (ident->isglobal) {
						MIPS_LA(v0, ident->name);
						MIPS_LW(v0, v0, 0);
					}
					else
						MIPS_LW(v0, sp, ident->addr);
				else {
					value = atoi(midcode[i].op1);
					MIPS_LI(v0, value);
				}
			}
			MIPS_LW(ra, sp, -4);		//退栈
			MIPS_LW(sp, sp, 0);
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
			if (ident1 == NULL) {
				value = atoi(midcode[i].op1);
				MIPS_LI(t0, value);
			}
			else {
				if (ident1->isglobal) {
					MIPS_LA(t0, ident1->name);
					MIPS_LW(t0, t0, 0);
				}
				else
					MIPS_LW(t0, sp, ident1->addr);
			}
			if (ident2 == NULL) {
				value = atoi(midcode[i].op2);
				MIPS_LI(t1, value);
			}
			else {
				if (ident2->isglobal) {
					MIPS_LA(t1, ident2->name);
					MIPS_LW(t1, t1, 0);
				}
				else
					MIPS_LW(t1, sp, ident2->addr);
			}
			if (ident->isglobal)
				MIPS_LA(t2, ident->name);
			else
				MIPS_ADDI(t2, sp, ident->addr);
			switch (midcode[i].op) {
			case PLUS:
				MIPS_ADD(t3, t0, t1);
				break;
			case MINUS:
				MIPS_SUB(t3, t0, t1);
				break;
			case TIMES:
				MIPS_MUL(t3, t0, t1);
				break;
			case DIVIDE:
				MIPS_DIV(t0, t1);
				MIPS_MFLO(t3);
				break;
			case EQU:
				MIPS_SEQ(t3, t0, t1);
				break;
			case LES:
				MIPS_SLT(t3, t0, t1);
				break;
			case GTR:
				MIPS_SGT(t3, t0, t1);
				break;
			case LEQ:
				MIPS_SLE(t3, t0, t1);
				break;
			case GEQ:
				MIPS_SGE(t3, t0, t1);
				break;
			case NEQ:
				MIPS_SNE(t3, t0, t1);
				break;
			}
			MIPS_SW(t3, t2, 0);
			break;
		case ASN:
			ident1 = Search(midcode[i].op1, 3);
			ident = Search(midcode[i].res, 3);
			if (ident1 == NULL) {
				value = atoi(midcode[i].op1);
				MIPS_LI(t0, value);
			}
			else {
				if (ident1->isglobal) {
					MIPS_LA(t0, ident1->name);
					MIPS_LW(t0, t0, 0);
				}
				else
					MIPS_LW(t0, sp, ident1->addr);
			}
			if (ident->isglobal)
				MIPS_LA(t1, ident->name);
			else
				MIPS_ADDI(t1, sp, ident->addr);
			MIPS_SW(t0, t1, 0);
			break;
		}
}

void AllocGlobal(Identity* ident, char* name, char* value) {
	if (ident == NULL)
		fprintf(targetcode, "%s: .asciiz %s\n", name, value);
	else {
		if (ident->kind == ARRAY) 
			fprintf(targetcode, "%s: .space %d\n", ident->name, ident->size * DATASIZE);
		else
			fprintf(targetcode, "%s: .word %d\n", ident->name, ident->value);
	}
}
void AllocLocal(Identity *&ident) {
	ident->addr = -offset * DATASIZE;
	if (ident->kind == CONST) {
		MIPS_LI(t0, ident->value);
		MIPS_SW(t0, sp, -offset * DATASIZE);
	}
	if (ident->kind == ARRAY)
		offset += ident->size;
	else
		offset++;
}
void PopPara(Identity ident) {
	MIPS_LW(t0, gp, top++ * DATASIZE);
	MIPS_SW(t0, sp, ident.addr);
}
void PushPara(Identity* ident, int value) {
	if (ident == NULL)
		MIPS_LI(t1, value);
	else {
		if (ident->isglobal) {
			MIPS_LA(t0, ident->name);
			MIPS_LW(t1, t0, 0);
		}
		else
			MIPS_LW(t1, sp, ident->addr);
	}
	MIPS_SW(t1, gp, 0);
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
	fprintf(targetcode, "\t addi %s, %s, 0x%x\n", reg[rt], reg[rs], value);
}
void MIPS_SUB(int rd, int rs, int rt) {
	fprintf(targetcode, "\t sub  %s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
}
void MIPS_SUBI(int rt, int rs, int value) {
	fprintf(targetcode, "\t subi %s, %s, 0x%x\n", reg[rt], reg[rs], value);
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