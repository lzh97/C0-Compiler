#include "stdafx.h"

extern FILE *source;
extern FILE *compilerecord;
extern FILE *tablerecord;
extern FILE *middlecode;
extern int cc, ll;
extern Symbol symbol;
extern char id[IdentityMaxLen];
extern int num;
extern Identity global[GlobalSize];
extern Identity local[LocalSize];
extern int gsize;
extern int lsize;
extern Quadruple midcode[1024];
extern int cnt;
extern Identity* current;

int level = 0;

void Tab();
void Excel();
char* Op2String(int op);

void LexicalTest() {
	Tab();
	switch (symbol) {
	case identity:
		fputs("Identity    ", compilerecord);
		fputs(id, compilerecord);
		break;
	case intconst:
		fputs("IntConst    ", compilerecord);
		char tmp[100];
		_itoa_s(num, tmp, 10);
		fputs(tmp, compilerecord);
		break;
	case charconst:
		fputs("CharConst   ", compilerecord);
		fputs(id, compilerecord);
		break;
	case stringconst:
		fputs("StringConst ", compilerecord);
		fputs(id, compilerecord);
		break;
	case voidsym:
		fputs("VoidSym     void", compilerecord);
		break;
	case intsym:
		fputs("IntSym      int", compilerecord);
		break;
	case charsym:
		fputs("CharSym     char", compilerecord);
		break;
	case mainsym:
		fputs("MainSym     main", compilerecord);
		break;
	case dosym:
		fputs("DoSym       do", compilerecord);
		break;
	case whilesym:
		fputs("WhileSym    while", compilerecord);
		break;
	case ifsym:
		fputs("IfSym       if", compilerecord);
		break;
	case switchsym:
		fputs("SwitchSym   switch", compilerecord);
		break;
	case casesym:
		fputs("CaseSym     case", compilerecord);
		break;
	case constsym:
		fputs("ConstSym    const", compilerecord);
		break;
	case scanfsym:
		fputs("ScanfSym    scanf", compilerecord);
		break;
	case printfsym:
		fputs("PrintfSym   printf", compilerecord);
		break;
	case returnsym:
		fputs("ReturnSym   return", compilerecord);
		break;
	case plus:
		fputs("Plus        +", compilerecord);
		break;
	case minus:
		fputs("Minus       -", compilerecord);
		break;
	case times:
		fputs("Times       *", compilerecord);
		break;
	case divide:
		fputs("Divide      /", compilerecord);
		break;
	case lpare:
		fputs("LPare       (", compilerecord);
		break;
	case rpare:
		fputs("RPare       )", compilerecord);
		break;
	case lbrak:
		fputs("LBrak       [", compilerecord);
		break;
	case rbrak:
		fputs("RBrak       ]", compilerecord);
		break;
	case lbrac:
		fputs("LBrac       {", compilerecord);
		break;
	case rbrac:
		fputs("RBrac       }", compilerecord);
		break;
	case assign:
		fputs("Assign      =", compilerecord);
		break;
	case equ:
		fputs("Equ         ==", compilerecord);
		break;
	case les:
		fputs("Les         <", compilerecord);
		break;
	case gtr:
		fputs("Gtr         >", compilerecord);
		break;
	case leq:
		fputs("Leq         <=", compilerecord);
		break;
	case geq:
		fputs("Geq         >=", compilerecord);
		break;
	case neq:
		fputs("Neq         !=", compilerecord);
		break;
	case comma:
		fputs("Comma       ,", compilerecord);
		break;
	case colon:
		fputs("Colon       :", compilerecord);
		break;
	case semic:
		fputs("Semic       ;", compilerecord);
		break;
	}
	fputs("\n", compilerecord);
}

void SyntaxTest(int code) {
	if ((code & 1) == 0) {
		Tab();
		level++;
	}
	else {
		level--;
		Tab();
	}
	switch (code) {
	case 0:
		fputs("<Program>", compilerecord);
		break;
	case 1:
		fputs("</Program>", compilerecord);
		break;
	case 2:
		fputs("<ConstantDeclare>", compilerecord);
		break;
	case 3:
		fputs("</ConstantDeclare>", compilerecord);
		break;
	case 4:
		fputs("<ConstantDefine>", compilerecord);
		break;
	case 5:
		fputs("</ConstantDefine>", compilerecord);
		break;
	case 6:
		fputs("<VariableDeclare>", compilerecord);
		break;
	case 7:
		fputs("</VariableDeclare>", compilerecord);
		break;
	case 8:
		fputs("<VariableDefine>(Maybe)", compilerecord);
		break;
	case 9:
		fputs("</VariableDefine>(Right)", compilerecord);
		break;
	case 11:
		fputs("</VariableDefine>(Wrong)", compilerecord);
		break;
	case 12:
		fputs("<FunctionDeclare or ProcedureDeclare>", compilerecord);
		break;
	case 13:
		fputs("</FunctionDeclare or ProcedureDeclare>", compilerecord);
		break;
	case 14:
		fputs("<FunctionDefine>", compilerecord);
		break;
	case 15:
		fputs("</FunctionDefine>", compilerecord);
		break;
	case 16:
		fputs("<ProcedureDefine>", compilerecord);
		break;
	case 17:
		fputs("</ProcedureDefine>", compilerecord);
		break;
	case 18:
		fputs("<ParameterTable>", compilerecord);
		break;
	case 19:
		fputs("</ParameterTable>", compilerecord);
		break;
	case 20:
		fputs("<MainDefine>", compilerecord);
		break;
	case 21:
		fputs("</MainDefine>", compilerecord);
		break;
	case 22:
		fputs("<CompoundStatement>", compilerecord);
		break;
	case 23:
		fputs("</CompoundStatement>", compilerecord);
		break;
	case 24:
		fputs("<Statements>", compilerecord);
		break;
	case 25:
		fputs("</Statements>", compilerecord);
		break;
	case 26:
		fputs("<Statement>", compilerecord);
		break;
	case 27:
		fputs("</Statement>", compilerecord);
		break;
	case 28:
		fputs("<IfStatement>", compilerecord);
		break;
	case 29:
		fputs("</IfStatement>", compilerecord);
		break;
	case 30:
		fputs("<DoWhileStatement>", compilerecord);
		break;
	case 31:
		fputs("</DoWhileStatement>", compilerecord);
		break;
	case 32:
		fputs("<SwitchStatemtn>", compilerecord);
		break;
	case 33:
		fputs("</SwitchStatement>", compilerecord);
		break;
	case 34:
		fputs("<AssignStatement>", compilerecord);
		break;
	case 35:
		fputs("</AssignStatement>", compilerecord);
		break;
	case 36:
		fputs("<ScanfStatement>", compilerecord);
		break;
	case 37:
		fputs("</ScanfStatement>", compilerecord);
		break;
	case 38:
		fputs("<PrintfStatement>", compilerecord);
		break;
	case 39:
		fputs("</PrintfStatement>", compilerecord);
		break;
	case 40:
		fputs("<ReturnStatement>", compilerecord);
		break;
	case 41:
		fputs("</ReturnStatement>", compilerecord);
		break;
	case 42:
		fputs("<FunctionCallStatement>", compilerecord);
		break;
	case 43:
		fputs("</FunctionCallStatement>", compilerecord);
		break;
	case 44:
		fputs("<ProcedureCallStatement>", compilerecord);
		break;
	case 45:
		fputs("</ProcedureCallStatement>", compilerecord);
		break;
	case 46:
		fputs("<Condition>", compilerecord);
		break;
	case 47:
		fputs("</Condition>", compilerecord);
		break;
	case 48:
		fputs("<SwitchTable>", compilerecord);
		break;
	case 49:
		fputs("</SwitchTable>", compilerecord);
		break;
	case 50:
		fputs("<ValueParameterTable>", compilerecord);
		break;
	case 51:
		fputs("</ValueParameterTable>", compilerecord);
		break;
	case 52:
		fputs("<Expression>", compilerecord);
		break;
	case 53:
		fputs("</Expression>", compilerecord);
		break;
	case 54:
		fputs("<Term>", compilerecord);
		break;
	case 55:
		fputs("</Term>", compilerecord);
		break;
	case 56:
		fputs("<Factor>", compilerecord);
		break;
	case 57:
		fputs("</Factor>", compilerecord);
		break;
	case 58:
		fputs("<Constant>", compilerecord);
		break;
	case 59:
		fputs("</Constant>", compilerecord);
		break;
	case 60:
		fputs("<Integer>", compilerecord);
		break;
	case 61:
		fputs("</Integer>", compilerecord);
		break;
	case 62:
		fputs("<VariableDefine>", compilerecord);
		break;
	case 63:
		fputs("</VariableDefine>", compilerecord);
		break;
	case 64:
		fputs("<Character>", compilerecord);
		break;
	case 65:
		fputs("</Character>", compilerecord);
		break;
	}
	fputs("\n", compilerecord);
}

void GlobalTableTest() {
	fprintf(tablerecord, "Global Table\n");
	Excel();
	fprintf(tablerecord, "|%10s|%10s|%10s|%10s|%10s|%10s|\n", "Name", "Kind", "Type", "Value", "Size", "Para");
	Excel();
	for (int i = 0; i < gsize; i++) {
		fprintf(tablerecord, "|%10s|%10d|%10d|%10d|%10d|%10d|\n", global[i].name, global[i].kind, global[i].type, global[i].value, global[i].size, global[i].paratype);
		Excel();
	}
	fprintf(tablerecord, "\n\n");
}

void LocalTableTest() {
	fprintf(tablerecord, "Local Table : %s\n", current->name);
	Excel();
	fprintf(tablerecord, "|%10s|%10s|%10s|%10s|%10s|%10s|\n", "Name", "Kind", "Type", "Value", "Size", "Para");
	Excel();
	for (int i = current->l; i < current->r; i++) {
		fprintf(tablerecord, "|%10s|%10d|%10d|%10d|%10d|%10d|\n", local[i].name, local[i].kind, local[i].type, local[i].value, local[i].size, local[i].paratype);
		Excel();
	}
	fprintf(tablerecord, "\n\n");
}

void QuadrupleTest() {
	for (int i = 0; i < cnt; i++)
		if(midcode[i].op != DEL)
			fprintf(middlecode, "%5s, %10s, %10s, %10s\n", Op2String(midcode[i].op), midcode[i].op1, midcode[i].op2, midcode[i].res);
}

void Tab() {
	for (int i = 0; i < level; i++)
		fputs("  ", compilerecord);
}
void Excel() {
	for (int i = 0; i < 67; i++)
		fprintf(tablerecord, "-");
	fprintf(tablerecord, "\n");
}
char* Op2String(int op) {
	switch (op)	{
	case CONST:return "const";
	case VAR:return "var";
	case ARR:return "arr";
	case PROC:return "proc";
	case FUNC:return "func";
	case PARA:return "para";
	case LABEL:return "label";
	case VAL:return "val";
	case CALL:return "call";
	case LARR:return "larr";
	case SARR:return "sarr";
	case JZ:return "jz";
	case JNZ:return "jnz";
	case SCAN:return "scan";
	case PRINTS:return "prints";
	case PRINTI:return "printi";
	case PRINTC:return "printc";
	case RET:return "ret";
	case PLUS:return "+";
	case MINUS:return "-";
	case TIMES:return "*";
	case DIVIDE:return "/";
	case EQU:return "==";
	case LES:return "<";
	case LEQ:return "<=";
	case GTR:return ">";
	case GEQ:return ">=";
	case NEQ:return "!=";
	case ASN:return "=";
	}
	return "";
}