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
void Condition(Identity *&ident, int* type, int* val);
void SwitchTable(Identity ident);
void ValueParaTable(Identity ident);
void Expression(Identity *&ident, int* type, int* val);
void Term(Identity *&ident, int* type, int* val);
void Factor(Identity *&ident, int* type, int* val);
void Constant();
void Integer();
void Character();

bool isRelationOp(int* op);
bool isAddingOp(int* op);
bool isMultiplyingOp(int* op);

//<程序>::=[<常量说明>][<变量说明>]{<有返回值函数定义> | <无返回值函数定义>}<主函数>
void Program() {
	SyntaxTest(0);
	NextSymbol();
	ConstDeclare(true);
	VarDeclare(true);
	FuncDeclare();
	MainDefine();
	SyntaxTest(1);
}

//<常量说明>::=const<常量定义>;{const<常量定义>;}
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

//<常量定义>::=int<标识符>=<整数>{,<标识符>=<整数>} | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
void ConstDefine(bool isglobal) {
	SyntaxTest(4);
	if (symbol == intsym) {
		type = INT;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == assign) {
				NextSymbol();
				Integer();
				AddConst(name, type, value, isglobal);
				GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
				while (symbol == comma) {
					NextSymbol();
					if (symbol == identity) {
						strcpy_s(name, id);
						NextSymbol();
						if (symbol == assign) {
							NextSymbol();
							Integer();
							AddConst(name, type, value, isglobal);
							GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
						}
						else
							Error(MISSING_ASSIGN_ERROR);
					}
					else
						Error(MISSING_IDENTITY_ERROR);
				}
			}
			else
				Error(MISSING_ASSIGN_ERROR);
		}
		else
			Error(MISSING_IDENTITY_ERROR);
	}
	else if (symbol == charsym) {
		type = CHAR;
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == assign) {
				NextSymbol();
				Character();
				AddConst(name, type, value, isglobal);
				GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
				while (symbol == comma) {
					NextSymbol();
					if (symbol == identity) {
						strcpy_s(name, id);
						NextSymbol();
						if (symbol == assign) {
							NextSymbol();
							Character();
							AddConst(name, type, value, isglobal);
							GenerateMidCode(CONST, Type2String(type), Int2String(value), name);
						}
						else
							Error(MISSING_ASSIGN_ERROR);
					}
					else
						Error(MISSING_IDENTITY_ERROR);
				}
			}
			else
				Error(MISSING_ASSIGN_ERROR);
		}
		else
			Error(MISSING_IDENTITY_ERROR);
	}
	else
		Error(MISSING_TYPE_ERROR);
	SyntaxTest(5);
}

//<变量说明>::=<变量定义>;{<变量定义>;}
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

//<变量定义>::=<类型标识符>(<标识符> | <标识符>'['<无符号整数>']'){,(<标识符> | <标识符>'['<无符号整数>']')}
//<类型标识符>::=int | char
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
					size = num;
					NextSymbol();
					if (symbol == rbrak) {
						AddArray(name, type, size, isglobal);
						GenerateMidCode(ARR, Type2String(type), Int2String(size), name);
						NextSymbol();
					}
					else
						Error(MISSING_RIGHT_BRACKET_ERROR);
				}
				else
					Error(MISSING_INDEX_ERROR);
			}
			else if (isglobal && symbol == lpare) {		//说明不是变量定义，为有返回值函数定义
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
							size = num;
							NextSymbol();
							if (symbol == rbrak) {
								AddArray(name, type, size, isglobal);
								GenerateMidCode(ARR, Type2String(type), Int2String(size), name);
								NextSymbol();
							}
							else
								Error(MISSING_RIGHT_BRACKET_ERROR);
						}
						else
							Error(MISSING_INDEX_ERROR);
					}
					else {
						AddVar(name, type, isglobal);
						GenerateMidCode(VAR, Type2String(type), "", name);
					}
				}
			}
		}
		else
			Error(MISSING_IDENTITY_ERROR);
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

//<有返回值函数定义> | <无返回值函数定义>
void FuncDeclare() {
	SyntaxTest(12);
	while (maindefinestate == 0) {
		if (funcdefinestate == 1)
			FuncDefine();
		else if (symbol == intsym || symbol == charsym)
			FuncDefine();
		else if (symbol == voidsym)
			ProcDefine();
		else
			Error(SYNTAX_ERROR);
	}
	SyntaxTest(13);
}

//<有返回值函数定义>::=<声明头部>'('<参数表>')''{'<复合语句>'}'
//<声明头部>::=int<标识符> | char<标识符>
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
			if (symbol == lpare) {
			l1:
				GenerateMidCode(FUNC, Type2String(type), "", name);
				NextSymbol();
				current = AddFunc(name, type);
				current->l = current->r = lsize;
				ParaTable();
				current->size = size;
				current->paratype = paratype;
				if (symbol == rpare) {
					NextSymbol();
					if (symbol == lbrac) {
						NextSymbol();
						CompoundStatement();
						if (symbol == rbrac) {
							LocalTableTest();
							NextSymbol();
						}
						else
							Error(MISSING_RIGHT_BRACE_ERROR);
					}
					else
						Error(MISSING_LEFT_BRACE_ERROR);
				}
				else
					Error(MISSING_RIGHT_PARENTHESIS_ERROR);
			}
			else
				Error(MISSING_LEFT_PARENTHESIS_ERROR);
		}
		else
			Error(MISSING_IDENTITY_ERROR);
	}
	SyntaxTest(15);
}

//<无返回值函数定义>::=void<标识符>'('<参数表>')''{'<复合语句>'}'
void ProcDefine() {
	SyntaxTest(16);
	if (symbol == voidsym) {
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			NextSymbol();
			if (symbol == lpare) {
				GenerateMidCode(PROC, "", "", name);
				NextSymbol();
				current = AddProc(name);
				current->l = current->r = lsize;
				ParaTable();
				current->size = size;
				current->paratype = paratype;
				if (symbol == rpare) {
					NextSymbol();
					if (symbol == lbrac) {
						NextSymbol();
						CompoundStatement();
						if (symbol == rbrac) {
							LocalTableTest();
							NextSymbol();
						}
						else
							Error(MISSING_RIGHT_BRACE_ERROR);
					}
					else
						Error(MISSING_LEFT_BRACE_ERROR);
				}
				else
					Error(MISSING_RIGHT_PARENTHESIS_ERROR);
			}
			else
				Error(MISSING_LEFT_PARENTHESIS_ERROR);
		}
		else if (symbol == mainsym)
			maindefinestate = 1;
		else
			Error(MISSING_IDENTITY_ERROR);
	}
	SyntaxTest(17);
}

//<参数表>::=<类型标识符><标识符＞{,<类型标识符><标识符>} | <空>
//<类型标识符>::=int | char
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
			GenerateMidCode(PARA, Type2String(type), "", name);
			NextSymbol();
			goto l1;
		}
		else
			Error(MISSING_IDENTITY_ERROR);
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
					GenerateMidCode(PARA, Type2String(type), "", name);
				}
				else
					Error(PARAMETER_NUM_OUTOFRANGE_ERROR);
				NextSymbol();
			}
			else
				Error(MISSING_IDENTITY_ERROR);
		}
		else
			Error(MISSING_TYPE_ERROR);
	}
l2:
	SyntaxTest(19);
}

//<主函数>::=void main‘(’‘)’ ‘{’＜复合语句＞‘}’
void MainDefine() {
	SyntaxTest(20);
	GlobalTableTest();
	NextSymbol();
	if (symbol == lpare) {
		NextSymbol();
		if (symbol == rpare) {
			NextSymbol();
			if (symbol == lbrac) {
				GenerateMidCode(PROC, "", "", "main");
				NextSymbol();
				current = AddProc("main");
				current->l = current->r = lsize;
				current->size = current->paratype = 0;
				CompoundStatement();
				LocalTableTest();
				if (symbol == rbrac) {

				}
				else
					Error(MISSING_RIGHT_BRACE_ERROR);
			}
			else
				Error(MISSING_LEFT_BRACE_ERROR);
		}
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	}
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	SyntaxTest(21);
}

//<复合语句>::=[<常量说明>][<变量说明>]<语句列>
void CompoundStatement() {
	SyntaxTest(22);
	ConstDeclare(false);
	VarDeclare(false);
	Statements();
	GenerateMidCode(RET, "", "", "");
	SyntaxTest(23);
}

//<语句列>::={<语句>}
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

//<语句>::=<条件语句> | <循环语句> | <情况语句> | '{'<语句列>'}' | <有返回值函数调用语句>; | <无返回值函数调用语句>; | <赋值语句>; | <读语句>; | <写语句>; | <空>; | <返回语句>;
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
			else
				Error(NOT_FUNCTION_ERROR);
		}
		else {
			if (ident->kind == VARIABLE || ident->kind == PARAMETER || ident->kind == ARRAY)
				AssignStatement(*ident);
			else
				Error(CANNOT_ASSIGN_IDENTITY_ERROR);
		}
		if (symbol == semic)
			NextSymbol();
		else
			Error(MISSING_SEMICOLON_ERROR);
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

//<条件语句>::=if'('<条件>')'<语句>
void IfStatement() {
	SyntaxTest(28);
	NextSymbol();
	if (symbol == lpare) {
		NextSymbol();
		Identity* ident = NULL;
		int type, val;
		Condition(ident, &type, &val);
		int l = NewLabel();
		if (ident == NULL)
			GenerateMidCode(JZ, Int2String(val), Label(l), "");
		else
			GenerateMidCode(JZ, ident->name, Label(l), "");
		if (symbol == rpare) {
			NextSymbol();
			Statement();
		}
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
		GenerateMidCode(LABEL, Label(l), "", "");
	}
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	SyntaxTest(29);
}

//<循环语句>::=do<语句>while'('<条件>')'
void DoWhileStatement() {
	SyntaxTest(30);
	NextSymbol();
	int l = NewLabel();
	GenerateMidCode(LABEL, Label(l), "", "");
	Statement();
	if (symbol == whilesym) {
		NextSymbol();
		if (symbol == lpare) {
			NextSymbol();
			Identity* ident = NULL;
			int type, val;
			Condition(ident, &type, &val);
			if (ident == NULL)
				GenerateMidCode(JNZ, Int2String(val), Label(l), "");
			else
				GenerateMidCode(JNZ, ident->name, Label(l), "");
			if (symbol == rpare) {
				NextSymbol();
			}
			else
				Error(MISSING_RIGHT_PARENTHESIS_ERROR);
		}
		else
			Error(MISSING_LEFT_PARENTHESIS_ERROR);
	}
	else
		Error(MISSING_WHILE_ERROR);
	SyntaxTest(31);
}

//<情况语句>::=switch'('<表达式>')''{'<情况表>'}'
void SwitchStatement() {
	SyntaxTest(32);
	NextSymbol();
	if (symbol == lpare) {
		NextSymbol();
		Identity* ident = NULL;
		int type, val;
		Expression(ident, &type, &val);
		if (symbol == rpare) {
			NextSymbol();
			if (symbol == lbrac) {
				NextSymbol();
				SwitchTable(*ident);
				if (symbol == rbrac) {
					NextSymbol();
				}
				else
					Error(MISSING_RIGHT_BRACE_ERROR);
			}
			else
				Error(MISSING_LEFT_BRACE_ERROR);
		}
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	}
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	SyntaxTest(33);
}

//<赋值语句>::=<标识符>=<表达式> | <标识符>'['<表达式>']'=<表达式>
void AssignStatement(Identity ident) {
	SyntaxTest(34);
	if (symbol == lbrak) {
		if (ident.kind != ARRAY)
			Error(NOT_ARRAY_ERROR);
		else {
			NextSymbol();
			Identity* ident1 = NULL;
			int type1, val1;
			Expression(ident1, &type1, &val1);
			if ((ident1 == NULL && type1 == CHAR) || (ident1 != NULL && ident1->type == CHAR))
				Error(INDEX_TYPE_ERROR);
			else if (ident1 == NULL && type1 == INT && (val1 < 0 || val1 > ident.size))
				Error(INDEX_OUTOFRANGE_ERROR);
			else {
				if (symbol == rbrak) {
					NextSymbol();
					if (symbol == assign) {
						NextSymbol();
						Identity* ident2 = NULL;
						int type2, val2;
						Expression(ident2, &type2, &val2);
						if (ident2 == NULL) {
							if (ident.type == CHAR && type2 == INT)
								Warning(ASSIGN_INTTOCHAR_WARNING);
							ch = val2;
							if (!isLetter())
								Error(INVALID_CHARACTER_ERROR);
							else if (ident1 == NULL)
								GenerateMidCode(SARR, Int2String(val2), Int2String(val1), ident.name);
							else
								GenerateMidCode(SARR, Int2String(val2), ident1->name, ident.name);
						}
						else {
							if (ident.type == CHAR && ident2->type == INT)
								Warning(ASSIGN_INTTOCHAR_WARNING);
							if (ident1 == NULL)
								GenerateMidCode(SARR, ident2->name, Int2String(val1), ident.name);
							else
								GenerateMidCode(SARR, ident2->name, ident1->name, ident.name);
						}
					}
					else
						Error(MISSING_ASSIGN_ERROR);
				}
				else
					Error(MISSING_RIGHT_BRACKET_ERROR);
			}
		}
	}
	else if (symbol == assign) {
		NextSymbol();
		Identity* ident1 = NULL;
		int type1, val1;
		Expression(ident1, &type1, &val1);
		if (ident1 == NULL) {
			if (ident.type == CHAR && type1 == INT)
				Warning(ASSIGN_INTTOCHAR_WARNING);
			ch = val1;
			if (!isLetter())
				Error(INVALID_CHARACTER_ERROR);
			else
				GenerateMidCode(ASN, Int2String(val1), "", ident.name);
		}
		else {
			if (ident.type == CHAR && ident1->type == INT)
				Warning(ASSIGN_INTTOCHAR_WARNING);
			GenerateMidCode(ASN, ident1->name, "", ident.name);
		}
	}
	else
		Error(MISSING_ASSIGN_ERROR);
	SyntaxTest(35);
}

//<读语句>::=scanf'('<标识符>{,<标识符>}')'
void ScanfStatement() {
	SyntaxTest(36);
	NextSymbol();
	if (symbol == lpare) {
		NextSymbol();
		if (symbol == identity) {
			strcpy_s(name, id);
			Identity* ident = Search(name, 3);
			if (ident == NULL)
				Error(UNDEFINED_IDENTITY_ERROR);
			else if (ident->kind != VARIABLE && ident->kind != PARAMETER)
				Error(CANNOT_ASSIGN_IDENTITY_ERROR);
			else
				GenerateMidCode(SCAN, "", "", name);
			NextSymbol();
			while (symbol == comma) {
				NextSymbol();
				if (symbol == identity) {
					strcpy_s(name, id);
					Identity* ident = Search(name, 3);
					if (ident == NULL)
						Error(UNDEFINED_IDENTITY_ERROR);
					else if (ident->kind != VARIABLE && ident->kind != PARAMETER)
						Error(CANNOT_ASSIGN_IDENTITY_ERROR);
					else
						GenerateMidCode(SCAN, "", "", name);
					NextSymbol();
				}
				else
					Error(MISSING_IDENTITY_ERROR);
			}
			if (symbol == rpare) {
				NextSymbol();
			}
			else
				Error(MISSING_RIGHT_PARENTHESIS_ERROR);
		}
		else
			Error(MISSING_IDENTITY_ERROR);
	}
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	SyntaxTest(37);
}

//<写语句>::=printf'('<字符串>,<表达式>')' | printf'('<字符串>')' | printf'('<表达式>')'
void PrintfStatement() {
	SyntaxTest(38);
	NextSymbol();
	if (symbol == lpare) {
		NextSymbol();
		if (symbol == stringconst) {
			char tmp[CodeMaxLen] = "\"";
			strcat_s(tmp, id);
			strcat_s(tmp, "\"");
			GenerateMidCode(PRINTS, tmp, "", "");
			NextSymbol();
			if (symbol == comma) {
				NextSymbol();
				Identity* ident = NULL;
				int type, val;
				Expression(ident, &type, &val);
				if (ident == NULL)
					if (type == INT)
						GenerateMidCode(PRINTI, Int2String(val), "", "");
					else
						GenerateMidCode(PRINTC, Int2String(val), "", "");
				else
					if (ident->type == INT)
						GenerateMidCode(PRINTI, ident->name, "", "");
					else
						GenerateMidCode(PRINTC, ident->name, "", "");
			}
		}
		else {
			Identity* ident = NULL;
			int type, val;
			Expression(ident, &type, &val);
			if (ident == NULL)
				if (type == INT)
					GenerateMidCode(PRINTI, Int2String(val), "", "");
				else
					GenerateMidCode(PRINTC, Int2String(val), "", "");
			else
				if (ident->type == INT)
					GenerateMidCode(PRINTI, ident->name, "", "");
				else
					GenerateMidCode(PRINTC, ident->name, "", "");
		}
		if (symbol == rpare) {
			NextSymbol();
		}
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	}
	else
		Error(MISSING_LEFT_PARENTHESIS_ERROR);
	SyntaxTest(39);
}

//<返回语句>::=return['('<表达式>')']
void ReturnStatement() {
	SyntaxTest(40);
	NextSymbol();
	if (symbol == lpare) {
		NextSymbol();
		Identity* ident = NULL;
		int type, val;
		Expression(ident, &type, &val);
		if (ident == NULL)
			GenerateMidCode(RET, Int2String(val), "", "");
		else
			GenerateMidCode(RET, ident->name, "", "");
		if (symbol == rpare)
			NextSymbol();
		else
			Error(MISSING_RIGHT_BRACE_ERROR);
	}
	else
		GenerateMidCode(RET, "", "", "");
	SyntaxTest(41);
}

//<有返回值函数调用语句>::=<标识符>'('<值参数表>')'
void FuncCallStatement(Identity ident) {
	SyntaxTest(42);
	ValueParaTable(ident);
	if (symbol == rpare)
		NextSymbol();
	else
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	SyntaxTest(43);
}

//<无返回值函数调用语句>::=<标识符>'('<值参数表>')'
void ProcCallStatement(Identity ident) {
	SyntaxTest(44);
	ValueParaTable(ident);
	if (symbol == rpare)
		NextSymbol();
	else 
		Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	SyntaxTest(45);
}

//<条件>::=<表达式><关系运算符><表达式> | <表达式>	//表达式为0条件为假，否则为真
void Condition(Identity *&ident, int* type, int* val) {
	SyntaxTest(46);
	Identity* ident1 = NULL;
	int type1, val1;
	Expression(ident1, &type1, &val1);
	int op;
	if (isRelationOp(&op)) {
		NextSymbol();
		Identity* ident2 = NULL;
		int type2, val2;
		Expression(ident2, &type2, &val2);
		int t = NewTempVar();
		ident = AddVar(TempVar(t), INT, false);
		if (ident1 == NULL)
			if (ident2 == NULL)
				GenerateMidCode(op, Int2String(val1), Int2String(val2), TempVar(t));
			else
				GenerateMidCode(op, Int2String(val1), ident2->name, TempVar(t));
		else
			if (ident2 == NULL)
				GenerateMidCode(op, ident1->name, Int2String(val2), TempVar(t));
			else
				GenerateMidCode(op, ident1->name, ident2->name, TempVar(t));
	}
	else{
		if (ident1 == NULL) {
			ident = NULL;
			*type = type1;
			*val = val1;
		}
		else
			ident = ident1;
	}
	SyntaxTest(47);
}

//<情况表>::=<情况子语句>{<情况子语句>}
//<情况子语句>::=case<常量>:<语句>
void SwitchTable(Identity ident) {
	SyntaxTest(48);
	do {
		if (symbol == casesym) {
			NextSymbol();
			Constant();
			if (ident.type != type)
				Error(UNMATCHED_TYPE_ERROR);
			else {
				int t = NewTempVar();
				AddVar(TempVar(t), type, false);
				GenerateMidCode(EQU, ident.name, Int2String(value), TempVar(t));
				int l = NewLabel();
				GenerateMidCode(JZ, TempVar(t), Label(l), "");
				if (symbol == colon) {
					NextSymbol();
					Statement();
				}
				else
					Error(MISSING_COLON_ERROR);
				GenerateMidCode(LABEL, Label(l), "", "");
			}
		}
		else
			Error(MISSING_CASE_ERROR);
	} while (symbol == casesym);
	SyntaxTest(49);
}

//<值参数表>::=<表达式>{,<表达式>} | <空>
void ValueParaTable(Identity ident) {
	SyntaxTest(50);
	int op;
	int size = 0;
	paratype = 0;
	if (isAddingOp(&op) || symbol == identity || symbol == intconst || symbol == charconst || symbol == lpare) {
		Identity* ident1 = NULL;
		int type1, val1;
		Expression(ident1, &type1, &val1);
		if (ident1 == NULL) {
			type = type1;
			GenerateMidCode(VAL, Int2String(val1), "", "");
		}
		else {
			type = ident1->type;
			GenerateMidCode(VAL, ident1->name, "", "");
		}
		paratype |= type << size;
		size++;
		while (symbol == comma) {
			NextSymbol();
			Expression(ident1, &type1, &val1);
			if (ident1 == NULL) {
				type = type1;
				GenerateMidCode(VAL, Int2String(val1), "", "");
			}
			else {
				type = ident1->type;
				GenerateMidCode(VAL, ident1->name, "", "");
			}
			paratype |= type << size;
			size++;
		}
	}
	if (ident.size != size)
		Error(UNMATCHED_PARA_NUM_ERROR);
	else if (ident.paratype != paratype)
		Error(UNMATCHED_PARA_TYPE_ERROR);
	SyntaxTest(51);
}

//<表达式>::=[+ | -]<项>{<加法运算符><项>}
void Expression(Identity *&ident, int* type, int* val) {
	SyntaxTest(52);
	int op;
	int sign = 1;
	if (isAddingOp(&op)) {
		sign = symbol == minus ? -1 : 1;
		NextSymbol();
	}
	Identity *ident1 = NULL, *ident3 = NULL;
	int type1, val1;
	Term(ident1, &type1, &val1);
	if (sign == -1) {
		int t = NewTempVar();
		ident3 = AddVar(TempVar(t), INT, false);
		if (ident1 == NULL)
			GenerateMidCode(MINUS, Int2String(0), Int2String(val1), ident3->name);
		else
			GenerateMidCode(MINUS, Int2String(0), ident1->name, ident3->name);
		ident1 = ident3;
	}
	while (isAddingOp(&op)) {
		NextSymbol();
		Identity* ident2 = NULL;
		int type2, val2;
		Term(ident2, &type2, &val2);
		int t = NewTempVar();
		ident3 = AddVar(TempVar(t), INT, false);
		if (ident2 == NULL)
			if (ident1 == NULL)
				GenerateMidCode(op, Int2String(val1), Int2String(val2), ident3->name);
			else
				GenerateMidCode(op, ident1->name, Int2String(val2), ident3->name);
		else
			if (ident1 == NULL)
				GenerateMidCode(op, Int2String(val1), ident2->name, ident3->name);
			else
				GenerateMidCode(op, ident1->name, ident2->name, ident3->name);
		ident1 = ident3;
	}
	ident = ident1;
	*type = type1;
	*val = val1;
	SyntaxTest(53);
}

//<项>::=<因子>{<乘法运算符><因子>}
void Term(Identity *&ident, int* type, int* val) {
	SyntaxTest(54);
	int op;
	Identity *ident1 = NULL, *ident3 = NULL;
	int type1, val1;
	Factor(ident1, &type1, &val1);
	while (isMultiplyingOp(&op)) {
		NextSymbol();
		Identity* ident2 = NULL;
		int type2, val2;
		Factor(ident2, &type2, &val2);
		int t = NewTempVar();
		ident3 = AddVar(TempVar(t), INT, false);
		if (ident2 == NULL)
			if (ident1 == NULL)
				GenerateMidCode(op, Int2String(val1), Int2String(val2), ident3->name);
			else
				GenerateMidCode(op, ident1->name, Int2String(val2), ident3->name);
		else
			if (ident1 == NULL)
				GenerateMidCode(op, Int2String(val1), ident2->name, ident3->name);
			else
				GenerateMidCode(op, ident1->name, ident2->name, ident3->name);
		ident1 = ident3;
	}
	ident = ident1;
	*type = type1;
	*val = val1;
	SyntaxTest(55);
}

//<因子>::=<标识符> | <标识符>'['<表达式>']'| <整数> | <字符> | <有返回值函数调用语句> | '('<表达式>')'
void Factor(Identity *&ident, int* type, int* val) {
	SyntaxTest(56);
	int op;
	if (symbol == identity) {
		strcpy_s(name, id);
		Identity* ident1 = Search(name, 3);
		if (ident1 == NULL)
			Error(UNDEFINED_IDENTITY_ERROR);
		else {
			NextSymbol();
			if (symbol == lbrak) {
				if (ident1->kind != ARRAY)
					Error(NOT_ARRAY_ERROR);
				else {
					NextSymbol();
					Identity* ident2 = NULL;
					int type2, val2;
					Expression(ident2, &type2, &val2);
					if ((ident2 == NULL && type2 == CHAR) || (ident2 != NULL && ident2->type == CHAR))
						Error(INDEX_TYPE_ERROR);
					else if (ident2 == NULL && type2 == INT && (val2 < 0 || val2 > ident1->size))
						Error(INDEX_OUTOFRANGE_ERROR);
					else {
						int t = NewTempVar();
						ident = AddVar(TempVar(t), ident1->type, false);
						if (ident2 == NULL)
							GenerateMidCode(LARR, ident1->name, Int2String(val2), ident->name);
						else
							GenerateMidCode(LARR, ident1->name, ident2->name, ident->name);
						if (symbol == rbrak)
							NextSymbol();
						else
							Error(MISSING_RIGHT_BRACKET_ERROR);
					}
				}
			}
			else if (symbol == lpare) {
				if (ident1->kind != FUNCTION)
					Error(NOT_FUNCTION_ERROR);
				else {
					NextSymbol();
					FuncCallStatement(*ident1);
					int t = NewTempVar();
					ident = AddVar(TempVar(t), ident1->type, false);
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
		*type = INT;
		*val = value;
	}
	else if (symbol == charconst) {
		Character();
		*type = CHAR;
		*val = value;
	}
	else if (symbol == lpare) {
		NextSymbol();
		Identity* ident2 = NULL;
		int type2, val2;
		Expression(ident2, &type2, &val2);
		ident = ident2;
		*type = type2;
		*val = val2;
		if (symbol == rpare) {
			NextSymbol();
		}
		else
			Error(MISSING_RIGHT_PARENTHESIS_ERROR);
	}
	else
		Error(EMPTY_FACTOR_ERROR);
	SyntaxTest(57);
}

//<常量>::=<整数> | <字符>
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

//<整数>::=[＋ | －]<无符号整数> | 0
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