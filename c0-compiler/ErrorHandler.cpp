#include "stdafx.h"

extern int ln;
extern int lc;
extern char ch;
extern char id[IdentityMaxLen];
extern char name[IdentityMaxLen];
extern bool success;
extern Symbol symbol;
extern int num;
extern Identity* current;

Symbol skipto[SymbolNum];
int count = 0;

char str[IdentityMaxLen];

void Skip();
void AddSkipTo(Symbol sym);
bool inSkipToSet();
char* Symbol2String(Symbol sym);

void Error(int code) {
	success = false;
	printf("Error : ");
	switch (code) {
	case FILE_NOT_EXIST_ERROR:
		printf("Source file does not exist");
		break;
	case PROGRAM_INCOMPLETE_ERROR:
		printf("Program incompleted");
		break;
	case INVALID_CHARACTER_ERROR:
		printf("In line %d, invalid character \'%c\'", lc, ch);
		break;
	case CHARACTER_LENGTH_ERROR:
		printf("In line %d, invalid character \'%s\'", lc, id);
		break;
	case INVALID_SYMBOL_ERROR:
		printf("In line %d, invalid symbol \"%c\"", lc, ch);
		break;
	case MISSING_SEMICOLON_ERROR:
		printf("In line %d, missing \';\'", lc);
		break;
	case MISSING_ASSIGN_ERROR:
		printf("In line %d, missing \'=\'", lc);
		break;
	case MISSING_IDENTITY_ERROR:
		printf("In line %d, missing identity", lc);
		break;
	case NOT_CHARACTER_ERROR:
		printf("In line %d, missing character constant", lc);
		break;
	case MISSING_TYPE_ERROR:
		printf("In line %d, missing type identity", lc);
		break;
	case MISSING_RIGHT_BRACKET_ERROR:
		printf("In line %d, missing \']\'", lc);
		break;
	case MISSING_INDEX_ERROR:
		printf("In line %d, missing array index", lc);
		break;
	case SYNTAX_ERROR:
		printf("In line %d, invalid syntax \"%s\"", lc, Symbol2String(symbol));
		break;
	case MISSING_RIGHT_BRACE_ERROR:
		printf("In line %d, missing \'}\'", lc);
		break;
	case MISSING_LEFT_BRACE_ERROR:
		printf("In line %d, missing \'{\'", lc);
		break;
	case MISSING_RIGHT_PARENTHESIS_ERROR:
		printf("In line %d, missing \')\'", lc);
		break;
	case MISSING_LEFT_PARENTHESIS_ERROR:
		printf("In line %d, missing \'(\'", lc);
		break;
	case PARAMETER_NUM_OUTOFRANGE_ERROR:
		printf("In line %d, too many parameters in function defination", lc);
		break;
	case MISSING_WHILE_ERROR:
		printf("In line %d, missing keyword \"while\"", lc);
		break;
	case MISSING_COLON_ERROR:
		printf("In line %d, missing \':\'", lc);
		break;
	case MISSING_CASE_ERROR:
		printf("In line %d, missing keyword \"case\"", lc);
		break;
	case EMPTY_FACTOR_ERROR:
		printf("In line %d, empty factor in expression", lc);
		break;
	case NOT_INTEGER_ERROR:
		printf("In line %d, missing integer constant", lc);
		break;
	case NOT_CONSTANT_ERROR:
		printf("In line %d, missing constant", lc);
		break;
	case DUPLICATE_DEFINATION_ERROR:
		printf("In line %d, duplicate defined \"%s\"", lc, name);
		break;
	case UNDEFINED_IDENTITY_ERROR:
		printf("In line %d, undefined \"%s\"", lc, name);
		break;
	case CANNOT_ASSIGN_IDENTITY_ERROR:
		printf("In line %d, cannot assign \"%s\"", lc, name);
		break;
	case NOT_ARRAY_ERROR:
		printf("In line %d, \"%s\" is not array", lc, name);
		break;
	case NOT_FUNCTION_ERROR:
		printf("In line %d, \"%s\" is not function", lc, name);
		break;
	case INDEX_TYPE_ERROR:
		printf("In line %d, array index type should be integer", lc);
		break;
	case INDEX_OUTOFRANGE_ERROR:
		printf("In line %d, array index is out of range", lc);
		break;
	case CANNOT_GETVALUE_IDENTITY_ERROR:
		printf("In line %d, cannot take the value of \"%s\"", lc, name);
		break;
	case UNMATCHED_TYPE_ERROR:
		printf("In line %d, unmatched type in switch statement", lc);
		break;
	case UNMATCHED_PARA_NUM_ERROR:
		printf("In line %d, unmatched parameter number in function call", lc);
		break;
	case UNMATCHED_PARA_TYPE_ERROR:
		printf("In line %d, unmatched parameter type in function call", lc);
		break;
	case MISSING_RETURN_VALUE_ERROR:
		printf("In function \"%s\", missing return value", current->name);
		break;
	case FUNC_RETURN_VALUE_ERROR:
		printf("In line %d, there is no return value", lc);
		break;
	case UNMATCHED_RETURN_TYPE_ERROR:
		printf("In line %d, unmatched return type for function \"%s\"", lc, current->name);
		break;
	}
	printf("\n");
}

void Warning(int code) {
	printf("Warning : ");
	switch (code) {
	case LEADING_ZERO_WARNING:
		printf("In line %d, there is leading zero in integer", lc);
		break;
	case ASSIGN_INTTOCHAR_WARNING:
		printf("In line %d, assigning integer to character", lc);
		break;
	case MAY_MISSING_RETURN_VALUE_WARNING:
		printf("In function \"%s\", probably missing return value", current->name);
		break;
	case PROC_RETURN_VALUE_WARNING:
		printf("In line %d, there is return value", lc);
		break;
	case DUPLICATE_CASE_WARNING:
		printf("In line %d, there is duplicate case", lc);
		break;
	case UNUSED_IDENTITY_WARNING:
		printf("Unused \"%s\"", name);
		break;
	}
	printf("\n");
}

void Skip() {
	while (!inSkipToSet())
		NextSymbol();
	count = 0;
}

void AddSkipTo(Symbol sym) {
	skipto[count++] = sym;
}

bool inSkipToSet() {
	for (int i = 0; i < count; i++)
		if (symbol == skipto[i])
			return true;
	return false;
}

char* Symbol2String(Symbol sym) {
	switch (sym) {
	case voidsym:return"void";
	case intsym:return"int";
	case charsym:return"char";
	case mainsym:return"main";
	case dosym:return"do";
	case whilesym:return"while";
	case ifsym:return"if";
	case switchsym:return"switch";
	case casesym:return"case";
	case constsym:return"const";
	case scanfsym:return"scanf";
	case printfsym:return"printf";
	case returnsym:return"return";
	case identity:strcpy_s(str, id); return str;
	case intconst:_itoa_s(num, str, 10); return str;
	case charconst:str[0] = ch; str[1] = '\0'; return str;
	case stringconst:strcpy_s(str, "\""); strcat_s(str, id); strcat_s(str, "\"");  return str;
	case plus:return"+";
	case minus:return"-";
	case times:return"*";
	case divide:return"/";
	case lpare:return"(";
	case rpare:return")";
	case lbrak:return"[";
	case rbrak:return"]";
	case lbrac:return"{";
	case rbrac:return"}";
	case assign:return"=";
	case equ:return"==";
	case les:return"<";
	case gtr:return">";
	case leq:return"<=";
	case geq:return">=";
	case neq:return"!=";
	case comma:return",";
	case colon:return":";
	case semic:return";";
	case none:str[0] = ch; str[1] = '\0'; return str;
	}
	return "";
}

void SkipConstDefine() {
	AddSkipTo(comma);
	AddSkipTo(semic);
	AddSkipTo(constsym);
	AddSkipTo(intsym);
	AddSkipTo(charsym);
	AddSkipTo(voidsym);
	Skip();
}
void SkipVarDefine() {
	AddSkipTo(rbrak);
	AddSkipTo(comma);
	AddSkipTo(semic);
	AddSkipTo(intsym);
	AddSkipTo(charsym);
	AddSkipTo(voidsym);
	Skip();
}
void SkipFuncDeclare() {
	AddSkipTo(intsym);
	AddSkipTo(charsym);
	AddSkipTo(voidsym);
	Skip();
}
void SkipParaTable() {
	AddSkipTo(comma);
	AddSkipTo(rpare);
	AddSkipTo(lbrac);
	AddSkipTo(rbrac);
	AddSkipTo(constsym);
	AddSkipTo(intsym);
	AddSkipTo(charsym);
	AddSkipTo(voidsym);
	Skip();
}
void SkipStatement() {
	AddSkipTo(comma);
	AddSkipTo(semic);
	AddSkipTo(lbrac);
	AddSkipTo(rbrac);
	AddSkipTo(ifsym);
	AddSkipTo(dosym);
	AddSkipTo(switchsym);
	AddSkipTo(identity);
	AddSkipTo(scanfsym);
	AddSkipTo(printfsym);
	AddSkipTo(returnsym);
	AddSkipTo(intsym);
	AddSkipTo(charsym);
	AddSkipTo(voidsym);
	Skip();
}
void SkipFactor() {
	AddSkipTo(semic);
	AddSkipTo(ifsym);
	AddSkipTo(dosym);
	AddSkipTo(switchsym);
	AddSkipTo(identity);
	AddSkipTo(scanfsym);
	AddSkipTo(printfsym);
	AddSkipTo(returnsym);
	AddSkipTo(plus);
	AddSkipTo(minus);
	AddSkipTo(times);
	AddSkipTo(divide);
	Skip();
}