#include "stdafx.h"

extern Symbol symbol;
extern char id[IdentityMaxLen];
extern char ch;
extern int num;
extern int lsize;

char name[IdentityMaxLen];
int value;
int type;
int size;
int paratype;

int funcdefinestate = 0;
int maindefinestate = 0;
int branchlevel = 0;
int returned;
Identity* current = NULL;

void ConstDeclare(bool isglobal);
void ConstDefine(bool isglobal);
void VarDeclare(bool isglobal);
void VarDefine(bool isglobal);
void FuncDeclare();
void ProcDefine();
void FuncDefine();
void ParaTable();
void MainDefine();
void CompoundStatement();
void Statements();
void Statement();
void IfStatement();
void DoWhileStatement();
void SwitchStatement();
void AssignStatement(Identity ident);
void ScanfStatement();
void PrintfStatement();
void ReturnStatement();
void FuncCallStatement(Identity ident);
void ProcCallStatement(Identity ident);
void Condition(Identity *&ident);
void SwitchTable(Identity ident);
void ValueParaTable(Identity ident);
void Expression(Identity *&ident);
void Term(Identity *&ident);
void Factor(Identity *&ident);
void Constant();
void Integer();
void Character();

bool isRelationOp(int* op);
bool isAddingOp(int* op);
bool isMultiplyingOp(int* op);

//<����>::=[<����˵��>][<����˵��>]{<�з���ֵ��������> | <�޷���ֵ��������>}<������>
void Program() {
	SyntaxTest(0);
	NextSymbol();
	ConstDeclare(true);
	VarDeclare(true);
	FuncDeclare();
	MainDefine();
	SyntaxTest(1);
}

//<����˵��>::=const<��������>;{const<��������>;}
void ConstDeclare(bool isglobal) {
	SyntaxTest(2);
	while (symbol == constsym) {
		NextSymbol();
		ConstDefine(isglobal);
		if (symbol == semic)
			NextSymbol();
		else
			Error(MISSING_SEMICOLON_ERROR);
	}
	SyntaxTest(3);
}

//<��������>::=int<��ʶ��>=<����>{,<��ʶ��>=<����>} | char����ʶ���������ַ���{,����ʶ���������ַ���}
void ConstDefine(bool isglobal) {
	SyntaxTest(4);
	if (symbol == intsym) {
		type = INT;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == assign)
				NextSymbol();
			else
				Error(MISSING_ASSIGN_ERROR);
			Integer();
			AddConst(name, type, value, isglobal);
			GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
		}
		else {
			Error(MISSING_IDENTITY_ERROR);
			SkipConstDefine();
		}
		while (symbol == comma) {
			NextSymbol();
			if (symbol == identity) {
				strcpy_s(name, id);
				NextSymbol();
				if (symbol == assign)
					NextSymbol();
				else
					Error(MISSING_ASSIGN_ERROR);
				Integer();
				AddConst(name, type, value, isglobal);
				GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
			}
			else {
				Error(MISSING_IDENTITY_ERROR);
				SkipConstDefine();
			}
		}
	}
	else if (symbol == charsym) {
		type = CHAR;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == assign)
				NextSymbol();
			else
				Error(MISSING_ASSIGN_ERROR);
			Character();
			AddConst(name, type, value, isglobal);
			GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
		}
		else {
			Error(MISSING_IDENTITY_ERROR);
			SkipConstDefine();
		}
		while (symbol == comma) {
			NextSymbol();
			if (symbol == identity) {
				strcpy_s(name, id);
				NextSymbol();
				if (symbol == assign)
					NextSymbol();
				else
					Error(MISSING_ASSIGN_ERROR);
				Character();
				AddConst(name, type, value, isglobal);
				GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
			}
			else {
				Error(MISSING_IDENTITY_ERROR);
				SkipConstDefine();
			}
		}
	}
	else{
		Error(MISSING_TYPE_ERROR);
		SkipConstDefine();
	}
	SyntaxTest(5);
}

//<����˵��>::=<��������>;{<��������>;}
void VarDeclare(bool isglobal) {
	SyntaxTest(6);
	funcdefinestate = 0;
	while (true) {
		VarDefine(isglobal);
		if (funcdefinestate != 0) 
			break;
		if (symbol == semic)
			NextSymbol();
		else
			Error(MISSING_SEMICOLON_ERROR);
	}
	SyntaxTest(7);
}

//<��������>::=<���ͱ�ʶ��>(<��ʶ��> | <��ʶ��>'['<�޷�������>']'){,(<��ʶ��> | <��ʶ��>'['<�޷�������>']')}
//<���ͱ�ʶ��>::=int | char
void VarDefine(bool isglobal) {
	if (isglobal)
		SyntaxTest(8);
	else
		SyntaxTest(62);
	if (symbol == intsym || symbol == charsym) {
		type = symbol == intsym ? INT : CHAR;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == lbrak) {
				NextSymbol();
				if (symbol == intconst) {
					AddArray(name, type, num, isglobal);
					GenerateMidCode(ARR, Type2String(type), Int2String(num), name);
					NextSymbol();
				}
				else {
					Error(MISSING_INDEX_ERROR);
					SkipVarDefine();
				}
				if (symbol == rbrak)
					NextSymbol();
				else
					Error(MISSING_RIGHT_BRACKET_ERROR);
			}
			else if (isglobal && symbol == lpare) {		//˵�����Ǳ������壬Ϊ�з���ֵ��������
				funcdefinestate = 1;
				strcpy_s(name, id);
				SyntaxTest(11);
				return;
			}
			else {
				AddVar(name, type, isglobal);
				GenerateMidCode(VAR, Type2String(type), "", name);
			}
			while (symbol == comma) {
				NextSymbol();
				if (symbol == identity) {
					strcpy_s(name, id);
					NextSymbol();
					if (symbol == lbrak) {
						NextSymbol();
						if (symbol == intconst) {
							AddArray(name, type, num, isglobal);
							GenerateMidCode(ARR, Type2String(type), Int2String(num), name);
							NextSymbol();
						}
						else {
							Error(MISSING_INDEX_ERROR);
							SkipVarDefine();
						}
						if (symbol == rbrak)
							NextSymbol();
						else
							Error(MISSING_RIGHT_BRACKET_ERROR);
					}
					else {
						AddVar(name, type, isglobal);
						GenerateMidCode(VAR, Type2String(type), "", name);
					}
				}
				else {
					Error(MISSING_IDENTITY_ERROR);
					SkipVarDefine();
				}
			}
		}
		else {
			Error(MISSING_IDENTITY_ERROR);
			SkipVarDefine();
		}
	}
	else 
		funcdefinestate = 2;
	if (isglobal)
		if(funcdefinestate == 0)
			SyntaxTest(9);
		else
			SyntaxTest(11);
	else
		SyntaxTest(63);
}

//<�з���ֵ��������> | <�޷���ֵ��������>
void FuncDeclare() {
	SyntaxTest(12);
	while (maindefinestate == 0) {
		if (funcdefinestate == 1)
			FuncDefine();
		else if (symbol == intsym || symbol == charsym)
			FuncDefine();
		else if (symbol == voidsym)
			ProcDefine();
		else {
			Error(SYNTAX_ERROR);
			SkipFuncDeclare();
		}
	}
	SyntaxTest(13);
}

//<�з���ֵ��������>::=<����ͷ��>'('<������>')''{'<�������>'}'
//<����ͷ��>::=int<��ʶ��> | char<��ʶ��>
void FuncDefine() {
	SyntaxTest(14);
	if (funcdefinestate == 1) {
		funcdefinestate = 0;
		goto l1;
	}
	if (symbol == intsym || symbol == charsym) {
		type = symbol == intsym ? INT : CHAR;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
		l1:
			if (symbol == lpare)
				NextSymbol();
			else
				Error(MISSING_LEFT_PARENTHESIS_ERROR);
			GenerateMidCode(FUNC, Type2String(type), "", name);
			current = AddFunc(name, type);
			current->l = current->r = lsize;
			ParaTable();
			current->size = size;
			current->paratype = paratype;
			if (symbol == rpare)
				NextSymbol();
			else
				Error(MISSING_RIGHT_PARENTHESIS_ERROR);
			if (symbol == lbrac)
				NextSymbol();
			else
				Error(MISSING_LEFT_BRACE_ERROR);
			returned = 0;
			CompoundStatement();
			if (returned == 0)
				Error(MISSING_RETURN_VALUE_ERROR);
			else if (returned == 1)
				Warning(MAY_MISSING_RETURN_VALUE_WARNING);
			if (returned != 2) {
				Identity* ident = AddConst(TempVar(NewTempVar()), current->type, 95, false);
				GenerateMidCode(RET, ident->name, "", "");
			}
			LocalTableTest();
			if (symbol == rbrac)
				NextSymbol();
			else
				Error(MISSING_RIGHT_BRACE_ERROR);
		}
		else {
			Error(MISSING_IDENTITY_ERROR);
			SkipFuncDeclare();
		}
	}
	SyntaxTest(15);
}

//<�޷���ֵ��������>::=void<��ʶ��>'('<������>')''{'<�������>'}'
void ProcDefine() {
	SyntaxTest(16);
	if (symbol == voidsym) {
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == lpare)
				NextSymbol();
			else
				Error(MISSING_LEFT_PARENTHESIS_ERROR);
			GenerateMidCode(PROC, "", "", name);
			current = AddProc(name);
			current->l = current->r = lsize;
			ParaTable();
			current->size = size;
			current->paratype = paratype;
			if (symbol == rpare)
				NextSymbol();
			else
				Error(MISSING_RIGHT_PARENTHESIS_ERROR);
			if (symbol == lbrac)
				NextSymbol();
			else
				Error(MISSING_LEFT_BRACE_ERROR);
			returned = 0;
			CompoundStatement();
			if (returned != 2)
				GenerateMidCode(RET, "", "", "");
			LocalTableTest();
			if (symbol == rbrac)
				NextSymbol();
			else
				Error(MISSING_RIGHT_BRACE_ERROR);
		}
		else if (symbol == mainsym)
			maindefinestate = 1;
		else {
			Error(MISSING_IDENTITY_ERROR);
			SkipFuncDeclare();
		}
	}
	SyntaxTest(17);
}

//<������>::=<���ͱ�ʶ��><��ʶ����{,<���ͱ�ʶ��><��ʶ��>} | <��>
//<���ͱ�ʶ��>::=int | char
void ParaTable() {
	SyntaxTest(18);
	unsigned int type;
	size = 0;
	paratype = 0;
	if (symbol == intsym || symbol == charsym) {
		type = symbol == intsym ? INT : CHAR;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			paratype |= type << size;
			size++;
			AddPara(name, type);
			GenerateMidCode(PARA, "", "", name);
			NextSymbol();
		}
		else {
			Error(MISSING_IDENTITY_ERROR);
			SkipParaTable();
		}
		goto l1;
	}
	goto l2;
l1:
	while (symbol == comma) {
		NextSymbol();
		if (symbol == intsym || symbol == charsym) {
			type = symbol == intsym ? INT : CHAR;
			NextSymbol();
			if (symbol == identity) {
				strcpy_s(name, id);
				if (size < ParaMaxNum) {
					paratype |= type << size;
					size++;
					AddPara(name, type);
					GenerateMidCode(PARA, "", "", name);
				}
				else
					Error(PARAMETER_NUM_OUTOFRANGE_ERROR);
				NextSymbol();
			}
			else {
				Error(MISSING_IDENTITY_ERROR);
				SkipParaTable();
			}
		}
		else {
			Error(MISSING_TYPE_ERROR);
			SkipParaTable();
		}
	}
l2:
	SyntaxTest(19);
}

//<������>::=void main��(����)�� ��{����������䣾��}��
void MainDefine() {
	SyntaxTest(20);
	GenerateMidCode(PROC, "", "", "main");
	current = AddProc("main");
	current->l = current->r = lsize;
	current->size = current->paratype = 0;
	NextSymbol();
	if (symbol == lpare)
		NextSymbol();
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	if (symbol == lbrac)
		NextSymbol();
	else
		Error(MISSING_LEFT_BRACE_ERROR);
	returned = 0;
	CompoundStatement();
	if (returned != 2)
		GenerateMidCode(RET, "", "", "");
	LocalTableTest();
	if (symbol == rbrac){
	}
	else
		Error(MISSING_RIGHT_BRACE_ERROR);
	GlobalTableTest();
	SyntaxTest(21);
}

//<�������>::=[<����˵��>][<����˵��>]<�����>
void CompoundStatement() {
	SyntaxTest(22);
	ConstDeclare(false);
	VarDeclare(false);
	Statements();
	SyntaxTest(23);
}

//<�����>::={<���>}
void Statements() {
	SyntaxTest(24);
	while (true) {
		if (symbol == ifsym || symbol == dosym || symbol == switchsym || symbol == lbrac || symbol == identity || symbol == scanfsym || symbol == printfsym || symbol == returnsym || symbol == semic)
			Statement();
		else
			break;
	}
	SyntaxTest(25);
}

//<���>::=<�������> | <ѭ�����> | <������> | '{'<�����>'}' | <�з���ֵ�����������>; | <�޷���ֵ�����������>; | <��ֵ���>; | <�����>; | <д���>; | <��>; | <�������>;
void Statement() {
	SyntaxTest(26);
	if (symbol == ifsym)
		IfStatement();
	else if (symbol == dosym)
		DoWhileStatement();
	else if (symbol == switchsym)
		SwitchStatement();
	else if (symbol == lbrac) {
		NextSymbol();
		Statements();
		if (symbol == rbrac)
			NextSymbol();
		else 
			Error(MISSING_RIGHT_BRACE_ERROR);
	}
	else if (symbol == identity) {
		strcpy_s(name, id);
		Identity* ident = Search(name, 3);
		NextSymbol();
		if (ident == NULL) {
			Error(UNDEFINED_IDENTITY_ERROR);
			SkipStatement();
		}
		else {
			if (symbol == lpare) {
				NextSymbol();
				if (ident->kind == PROCEDURE) {
					ProcCallStatement(*ident);
					GenerateMidCode(CALL, ident->name, "", "");
				}
				else if (ident->kind == FUNCTION) {
					FuncCallStatement(*ident);
					GenerateMidCode(CALL, ident->name, "", "");
				}
				else {
					Error(NOT_FUNCTION_ERROR);
					SkipStatement();
				}
			}
			else {
				if (ident->kind == VARIABLE || ident->kind == PARAMETER || ident->kind == ARRAY)
					AssignStatement(*ident);
				else {
					Error(CANNOT_ASSIGN_IDENTITY_ERROR);
					SkipStatement();
				}
			}
			if (symbol == semic)
				NextSymbol();
			else
				Error(MISSING_SEMICOLON_ERROR);
		}
	}
	else if (symbol == scanfsym) {
		ScanfStatement();
		if (symbol == semic)
			NextSymbol();
		else
			Error(MISSING_SEMICOLON_ERROR);
	}
	else if (symbol == printfsym) {
		PrintfStatement();
		if (symbol == semic)
			NextSymbol();
		else
			Error(MISSING_SEMICOLON_ERROR);
	}
	else if (symbol == returnsym){
		ReturnStatement();
		if (symbol == semic)
			NextSymbol();
		else
			Error(MISSING_SEMICOLON_ERROR);
	}
	else if (symbol == semic)
		NextSymbol();
	SyntaxTest(27);
}

//<�������>::=if'('<����>')'<���>
void IfStatement() {
	SyntaxTest(28);
	branchlevel++;
	NextSymbol();
	if (symbol == lpare)
		NextSymbol();
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	Identity* ident = NULL;
	Condition(ident);
	int l = NewLabel();
	GenerateMidCode(JZ, ident->name, Label(l), "");
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	Statement();
	GenerateMidCode(LABEL, Label(l), "", "");
	branchlevel--;
	SyntaxTest(29);
}

//<ѭ�����>::=do<���>while'('<����>')'
void DoWhileStatement() {
	SyntaxTest(30);
	int l = NewLabel();
	GenerateMidCode(LABEL, Label(l), "", "");
	NextSymbol();
	Statement();
	if (symbol == whilesym)
		NextSymbol();
	else
		Error(MISSING_WHILE_ERROR);
	if (symbol == lpare)
		NextSymbol();
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	Identity* ident = NULL;
	Condition(ident);
	GenerateMidCode(JNZ, ident->name, Label(l), "");
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	SyntaxTest(31);
}

//<������>::=switch'('<���ʽ>')''{'<�����>'}'
void SwitchStatement() {
	SyntaxTest(32);
	branchlevel++;
	NextSymbol();
	if (symbol == lpare)
		NextSymbol();
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	Identity* ident = NULL;
	Expression(ident);
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	if (symbol == lbrac)
		NextSymbol();
	else
		Error(MISSING_LEFT_BRACE_ERROR);
	SwitchTable(*ident);
	if (symbol == rbrac)
		NextSymbol();
	else
		Error(MISSING_RIGHT_BRACE_ERROR);
	branchlevel--;
	SyntaxTest(33);
}

//<��ֵ���>::=<��ʶ��>=<���ʽ> | <��ʶ��>'['<���ʽ>']'=<���ʽ>
void AssignStatement(Identity ident) {
	SyntaxTest(34);
	if (symbol == lbrak) {
		if (ident.kind != ARRAY)
			Error(NOT_ARRAY_ERROR);
		else {
			NextSymbol();
			Identity* ident1 = NULL;
			Expression(ident1);
			if (ident1->type == CHAR) {
				Error(INDEX_TYPE_ERROR);
				SkipStatement();
			}
			else if (ident1->kind == CONSTANT && (ident1->value < 0 || ident1->value > ident.size)) {
				Error(INDEX_OUTOFRANGE_ERROR);
				SkipStatement();
			}
			else {
				if (symbol == rbrak)
					NextSymbol();
				else
					Error(MISSING_RIGHT_BRACKET_ERROR);
				if (symbol == assign)
					NextSymbol();
				else
					Error(MISSING_ASSIGN_ERROR);
				Identity* ident2 = NULL;
				Expression(ident2);
				if (ident.type == CHAR && ident2->type == INT)
					Warning(ASSIGN_INTTOCHAR_WARNING);
				ch = ident2->value;
				if (ident.type == CHAR && ident2->kind == CONSTANT && !isValidChar()) {
					Error(INVALID_CHARACTER_ERROR);
					SkipStatement();
				}
				GenerateMidCode(SARR, ident2->name, ident1->name, ident.name);
			}
		}
	}
	else if (symbol == assign) {
		NextSymbol();
		Identity* ident1 = NULL;
		Expression(ident1);
		if (ident.type == CHAR && ident1->type == INT)
			Warning(ASSIGN_INTTOCHAR_WARNING);
		ch = ident1->value;
		if (ident.type == CHAR && ident1->kind == CONSTANT && !isValidChar()) {
			Error(INVALID_CHARACTER_ERROR);
			SkipStatement();
		}
		GenerateMidCode(ASN, ident1->name, "", ident.name);
	}
	else {
		Error(MISSING_ASSIGN_ERROR);
		SkipStatement();
	}
	SyntaxTest(35);
}

//<�����>::=scanf'('<��ʶ��>{,<��ʶ��>}')'
void ScanfStatement() {
	SyntaxTest(36);
	NextSymbol();
	if (symbol == lpare)
		NextSymbol();
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	if (symbol == identity) {
		strcpy_s(name, id);
		Identity* ident = Search(name, 3);
		if (ident == NULL) {
			Error(UNDEFINED_IDENTITY_ERROR);
			SkipStatement();
		}
		else if (ident->kind != VARIABLE && ident->kind != PARAMETER) {
			Error(CANNOT_ASSIGN_IDENTITY_ERROR);
			SkipStatement();
		}
		else
			GenerateMidCode(SCAN, "", "", name);
		NextSymbol();
		while (symbol == comma) {
			NextSymbol();
			if (symbol == identity) {
				strcpy_s(name, id);
				Identity* ident = Search(name, 3);
				if (ident == NULL) {
					Error(UNDEFINED_IDENTITY_ERROR);
					SkipStatement();
				}
				else if (ident->kind != VARIABLE && ident->kind != PARAMETER) {
					Error(CANNOT_ASSIGN_IDENTITY_ERROR);
					SkipStatement();
				}
				else
					GenerateMidCode(SCAN, "", "", name);
				NextSymbol();
			}
			else {
				Error(MISSING_IDENTITY_ERROR);
				SkipStatement();
			}
		}
		if (symbol == rpare)
			NextSymbol();
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	}
	else {
		Error(MISSING_IDENTITY_ERROR);
		SkipStatement();
	}
	SyntaxTest(37);
}

//<д���>::=printf'('<�ַ���>,<���ʽ>')' | printf'('<�ַ���>')' | printf'('<���ʽ>')'
void PrintfStatement() {
	SyntaxTest(38);
	NextSymbol();
	if (symbol == lpare)
		NextSymbol();
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	if (symbol == stringconst) {
		char tmp[CodeMaxLen] = "\"";
		strcat_s(tmp, id);
		strcat_s(tmp, "\"");
		GenerateMidCode(PRINTS, tmp, "", "");
		NextSymbol();
		if (symbol == comma) {
			NextSymbol();
			Identity* ident = NULL;
			Expression(ident);
			if (ident->type == INT)
				GenerateMidCode(PRINTI, ident->name, "", "");
			else
				GenerateMidCode(PRINTC, ident->name, "", "");
		}
	}
	else {
		Identity* ident = NULL;
		Expression(ident);
		if (ident->type == INT)
			GenerateMidCode(PRINTI, ident->name, "", "");
		else
			GenerateMidCode(PRINTC, ident->name, "", "");
	}
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	SyntaxTest(39);
}

//<�������>::=return['('<���ʽ>')']
void ReturnStatement() {
	SyntaxTest(40);
	NextSymbol();
	if (symbol == lpare) {
		if (current->kind == PROCEDURE)
			Warning(PROC_RETURN_VALUE_WARNING);
		if (returned != 2)
			if (branchlevel == 0)
				returned = 2;
			else
				returned = 1;
		NextSymbol();
		Identity* ident = NULL;
		Expression(ident);
		if (current->kind == FUNCTION && current->type != ident->type)
			Error(UNMATCHED_RETURN_TYPE_ERROR);
		GenerateMidCode(RET, ident->name, "", "");
		if (symbol == rpare)
			NextSymbol();
		else
			Error(MISSING_RIGHT_BRACE_ERROR);
	}
	else {
		if (current->kind == FUNCTION)
			Error(FUNC_RETURN_VALUE_ERROR);
		GenerateMidCode(RET, "", "", "");
	}
	SyntaxTest(41);
}

//<�з���ֵ�����������>::=<��ʶ��>'('<ֵ������>')'
void FuncCallStatement(Identity ident) {
	SyntaxTest(42);
	ValueParaTable(ident);
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	SyntaxTest(43);
}

//<�޷���ֵ�����������>::=<��ʶ��>'('<ֵ������>')'
void ProcCallStatement(Identity ident) {
	SyntaxTest(44);
	ValueParaTable(ident);
	if (symbol == rpare)
		NextSymbol();
	else 
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	SyntaxTest(45);
}

//<����>::=<���ʽ><��ϵ�����><���ʽ> | <���ʽ>	//���ʽΪ0����Ϊ�٣�����Ϊ��
void Condition(Identity *&ident) {
	SyntaxTest(46);
	Identity* ident1 = NULL;
	Expression(ident1);
	int op;
	if (isRelationOp(&op)) {
		NextSymbol();
		Identity* ident2 = NULL;
		Expression(ident2);
		ident = AddVar(TempVar(NewTempVar()), INT, false);
		GenerateMidCode(op, ident1->name, ident2->name, ident->name);
	}
	else
		ident = ident1;
	SyntaxTest(47);
}

//<�����>::=<��������>{<��������>}
//<��������>::=case<����>:<���>
void SwitchTable(Identity ident) {
	SyntaxTest(48);
	do {
		if (symbol == casesym)
			NextSymbol();
		else
			Error(MISSING_CASE_ERROR);
		Constant();
		if (ident.type != type)
			Error(UNMATCHED_TYPE_ERROR);
		else {
			Identity* ident1 = AddVar(TempVar(NewTempVar()), type, false);
			GenerateMidCode(EQU, ident.name, Int2String(value), ident1->name);
			int l = NewLabel();
			GenerateMidCode(JZ, ident1->name, Label(l), "");
			if (symbol == colon)
				NextSymbol();
			else
				Error(MISSING_COLON_ERROR);
			Statement();
			GenerateMidCode(LABEL, Label(l), "", "");
		}
	} while (symbol == casesym);
	SyntaxTest(49);
}

//<ֵ������>::=<���ʽ>{,<���ʽ>} | <��>
void ValueParaTable(Identity ident) {
	SyntaxTest(50);
	int op;
	int size = 0;
	paratype = 0;
	if (isAddingOp(&op) || symbol == identity || symbol == intconst || symbol == charconst || symbol == lpare) {
		Identity* ident1 = NULL;
		Expression(ident1);
		GenerateMidCode(VAL, ident1->name, "", "");
		paratype |= ident1->type << size;
		size++;
		while (symbol == comma) {
			NextSymbol();
			ident1 = NULL;
			Expression(ident1);
			GenerateMidCode(VAL, ident1->name, "", "");
			paratype |= ident1->type << size;
			size++;
		}
	}
	if (ident.size != size)
		Error(UNMATCHED_PARA_NUM_ERROR);
	else if (ident.paratype != paratype)
		Error(UNMATCHED_PARA_TYPE_ERROR);
	SyntaxTest(51);
}

//<���ʽ>::=[+ | -]<��>{<�ӷ������><��>}
void Expression(Identity *&ident) {
	SyntaxTest(52);
	int op;
	int sign = 1;
	if (isAddingOp(&op)) {
		sign = symbol == minus ? -1 : 1;
		NextSymbol();
	}
	Identity *ident1 = NULL, *ident3 = NULL;
	Term(ident1);
	if (sign == -1) {
		ident3 = AddVar(TempVar(NewTempVar()), INT, false);
		GenerateMidCode(MINUS, Int2String(0), ident1->name, ident3->name);
		ident1 = ident3;
	}
	while (isAddingOp(&op)) {
		NextSymbol();
		Identity* ident2 = NULL;
		Term(ident2);
		ident3 = AddVar(TempVar(NewTempVar()), INT, false);
		GenerateMidCode(op, ident1->name, ident2->name, ident3->name);
		ident1 = ident3;
	}
	ident = ident1;
	SyntaxTest(53);
}

//<��>::=<����>{<�˷������><����>}
void Term(Identity *&ident) {
	SyntaxTest(54);
	int op;
	Identity *ident1 = NULL, *ident3 = NULL;
	Factor(ident1);
	while (isMultiplyingOp(&op)) {
		NextSymbol();
		Identity* ident2 = NULL;
		Factor(ident2);
		ident3 = AddVar(TempVar(NewTempVar()), INT, false);
		GenerateMidCode(op, ident1->name, ident2->name, ident3->name);
		ident1 = ident3;
	}
	ident = ident1;
	SyntaxTest(55);
}

//<����>::=<��ʶ��> | <��ʶ��>'['<���ʽ>']'| <����> | <�ַ�> | <�з���ֵ�����������> | '('<���ʽ>')'
void Factor(Identity *&ident) {
	SyntaxTest(56);
	int op;
	if (symbol == identity) {
		strcpy_s(name, id);
		Identity* ident1 = Search(name, 3);
		if (ident1 == NULL) {
			Error(UNDEFINED_IDENTITY_ERROR);
			SkipFactor();
		}
		else {
			NextSymbol();
			if (symbol == lbrak) {
				if (ident1->kind != ARRAY) {
					Error(NOT_ARRAY_ERROR);
					SkipFactor();
				}
				else {
					NextSymbol();
					Identity* ident2 = NULL;
					Expression(ident2);
					if (ident2->type == CHAR)
						Error(INDEX_TYPE_ERROR);
					else if (ident2->kind == CONST && (ident2->value < 0 || ident2->value > ident1->size))
						Error(INDEX_OUTOFRANGE_ERROR);
					else {
						ident = AddVar(TempVar(NewTempVar()), ident1->type, false);
						GenerateMidCode(LARR, ident1->name, ident2->name, ident->name);
					}
					if (symbol == rbrak)
						NextSymbol();
					else
						Error(MISSING_RIGHT_BRACKET_ERROR);
				}
			}
			else if (symbol == lpare) {
				if (ident1->kind != FUNCTION) {
					Error(NOT_FUNCTION_ERROR);
					SkipFactor();
				}
				else {
					NextSymbol();
					FuncCallStatement(*ident1);
					ident = AddVar(TempVar(NewTempVar()), ident1->type, false);
					GenerateMidCode(CALL, ident1->name, "", ident->name);
				}
			}
			else {
				if (ident1->kind != CONSTANT && ident1->kind != VARIABLE && ident1->kind != PARAMETER)
					Error(CANNOT_GETVALUE_IDENTITY_ERROR);
				else
					ident = ident1;
			}
		}
	}
	else if (isAddingOp(&op) || symbol == intconst) {
		Integer();
		ident = AddConst(TempVar(NewTempVar()), INT, value, false);
	}
	else if (symbol == charconst) {
		Character();
		ident = AddConst(TempVar(NewTempVar()), CHAR, value, false);
	}
	else if (symbol == lpare) {
		NextSymbol();
		Identity* ident1 = NULL;
		Expression(ident1);
		ident = ident1;
		if (symbol == rpare)
			NextSymbol();
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	}
	else
		Error(EMPTY_FACTOR_ERROR);
	if (ident == NULL)
		ident = AddConst(TempVar(NewTempVar()), INT, 0, false);
	SyntaxTest(57);
}

//<����>::=<����> | <�ַ�>
void Constant() {
	SyntaxTest(58);
	int op;
	if (symbol == charconst)
		Character();
	else if (symbol == intconst || isAddingOp(&op))
		Integer();
	else
		Error(NOT_CONSTANT_ERROR);
	SyntaxTest(59);
}

//<����>::=[�� | ��]<�޷�������> | 0
void Integer() {
	SyntaxTest(60);
	int op;
	int sign = 1;
	if (isAddingOp(&op)) {
		sign = symbol == minus ? -1 : 1;
		NextSymbol();
	}
	if (symbol == intconst) {
		type = INT;
		value = num * sign;
		NextSymbol();
	}
	else
		Error(NOT_INTEGER_ERROR);
	SyntaxTest(61);
}

void Character() {
	SyntaxTest(64);
	if (symbol == charconst) {
		type = CHAR;
		value = (int)id[0];
		NextSymbol();
	}
	else
		Error(NOT_CHARACTER_ERROR);
	SyntaxTest(65);
}

bool isRelationOp(int* op) {
	switch (symbol){
	case equ:
		*op = EQU;
		return true;
	case les:
		*op = LES;
		return true;
	case gtr:
		*op = GTR;
		return true;
	case leq:
		*op = LEQ;
		return true;
	case geq:
		*op = GEQ;
		return true;
	case neq:
		*op = NEQ;
		return true;
	}
	return false;
}
bool isAddingOp(int* op) {
	switch (symbol) {
	case plus:
		*op = PLUS;
		return true;
	case minus:
		*op = MINUS;
		return true;
	}
	return false;
}
bool isMultiplyingOp(int* op) {
	switch (symbol) {
	case times:
		*op = TIMES;
		return true;
	case divide:
		*op = DIVIDE;
		return true;
	}
	return false;
}