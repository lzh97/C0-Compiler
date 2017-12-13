#include "stdafx.h"

extern int lc;
extern char ch;
extern char id[IdentityMaxLen];
extern char name[IdentityMaxLen];
extern bool success;

void Error(int code) {
	success = false;
	printf("Error :   ");
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
		printf("In line %d, unrecognized syntax", lc);
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
	}
	printf("\n");
}