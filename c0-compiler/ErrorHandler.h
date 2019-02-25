#pragma once

#define FILE_NOT_EXIST_ERROR 0					//文件不存在
#define PROGRAM_INCOMPLETE_ERROR 100			//程序不完整
#define INVALID_CHARACTER_ERROR 101				//无效字符
#define CHARACTER_LENGTH_ERROR 102				//字符长度不符
#define INVALID_SYMBOL_ERROR 103				//无效符号
#define MISSING_SEMICOLON_ERROR 200				//缺失分号
#define MISSING_ASSIGN_ERROR 201				//缺失赋值
#define MISSING_IDENTITY_ERROR 202				//缺失标识符
#define NOT_CHARACTER_ERROR 203					//非字符
#define MISSING_TYPE_ERROR 204					//缺失类型
#define MISSING_RIGHT_BRACKET_ERROR 205			//缺失右方括号
#define MISSING_INDEX_ERROR 206					//缺失数组下标
#define SYNTAX_ERROR 207						//语法错误
#define MISSING_RIGHT_BRACE_ERROR 208			//缺失右花括号
#define MISSING_LEFT_BRACE_ERROR 209			//缺失左花括号
#define MISSING_RIGHT_PARENTHESIS_ERROR 210		//缺失右圆括号
#define MISSING_LEFT_PARENTHESIS_ERROR 211		//缺失左圆括号
#define PARAMETER_NUM_OUTOFRANGE_ERROR 212		//参数个数溢出
#define MISSING_WHILE_ERROR 213					//缺失while关键字
#define MISSING_COLON_ERROR 214					//缺失冒号
#define MISSING_CASE_ERROR 215					//缺失case关键字
#define EMPTY_FACTOR_ERROR 216					//因子为空
#define NOT_INTEGER_ERROR 217					//非整数
#define NOT_CONSTANT_ERROR 218					//非常量
#define DUPLICATE_DEFINATION_ERROR 300			//重复定义标识符
#define UNDEFINED_IDENTITY_ERROR 301			//未定义标识符
#define CANNOT_ASSIGN_IDENTITY_ERROR 302		//不能赋值标识符
#define NOT_ARRAY_ERROR 303						//非数组
#define NOT_FUNCTION_ERROR 304					//非函数
#define INDEX_TYPE_ERROR 305					//下标类型错误
#define INDEX_OUTOFRANGE_ERROR 306				//下标越界
#define CANNOT_GETVALUE_IDENTITY_ERROR 307		//不能取值标识符
#define UNMATCHED_TYPE_ERROR 308				//类型不匹配
#define UNMATCHED_PARA_NUM_ERROR 309			//参数数量不匹配
#define UNMATCHED_PARA_TYPE_ERROR 310			//参数类型不匹配
#define MISSING_RETURN_VALUE_ERROR 311			//缺失返回值
#define FUNC_RETURN_VALUE_ERROR	312				//函数返回空值
#define UNMATCHED_RETURN_TYPE_ERROR 313			//函数返回类型不匹配

#define LEADING_ZERO_WARNING 100				//无符号整数前导零
#define ASSIGN_INTTOCHAR_WARNING 300			//整型赋值字符型
#define MAY_MISSING_RETURN_VALUE_WARNING 301	//可能缺失返回值
#define PROC_RETURN_VALUE_WARNING 302			//过程返回非空值
#define DUPLICATE_CASE_WARNING 303				//重复定义情况
#define UNUSED_IDENTITY_WARNING 304				//未使用标识符

void Error(int code);
void Warning(int code);

void SkipConstDefine();
void SkipVarDefine();
void SkipFuncDeclare();
void SkipParaTable();
void SkipStatement();
void SkipFactor();