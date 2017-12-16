#pragma once

#define FILE_NOT_EXIST_ERROR 0					//�ļ�������
#define PROGRAM_INCOMPLETE_ERROR 100			//��������
#define INVALID_CHARACTER_ERROR 101				//��Ч�ַ�
#define CHARACTER_LENGTH_ERROR 102				//�ַ����Ȳ���
#define INVALID_SYMBOL_ERROR 103				//��Ч����
#define MISSING_SEMICOLON_ERROR 200				//ȱʧ�ֺ�
#define MISSING_ASSIGN_ERROR 201				//ȱʧ��ֵ
#define MISSING_IDENTITY_ERROR 202				//ȱʧ��ʶ��
#define NOT_CHARACTER_ERROR 203					//���ַ�
#define MISSING_TYPE_ERROR 204					//ȱʧ����
#define MISSING_RIGHT_BRACKET_ERROR 205			//ȱʧ�ҷ�����
#define MISSING_INDEX_ERROR 206					//ȱʧ�����±�
#define SYNTAX_ERROR 207						//�﷨����
#define MISSING_RIGHT_BRACE_ERROR 208			//ȱʧ�һ�����
#define MISSING_LEFT_BRACE_ERROR 209			//ȱʧ������
#define MISSING_RIGHT_PARENTHESIS_ERROR 210		//ȱʧ��Բ����
#define MISSING_LEFT_PARENTHESIS_ERROR 211		//ȱʧ��Բ����
#define PARAMETER_NUM_OUTOFRANGE_ERROR 212		//�����������
#define MISSING_WHILE_ERROR 213					//ȱʧwhile�ؼ���
#define MISSING_COLON_ERROR 214					//ȱʧð��
#define MISSING_CASE_ERROR 215					//ȱʧcase�ؼ���
#define EMPTY_FACTOR_ERROR 216					//����Ϊ��
#define NOT_INTEGER_ERROR 217					//������
#define NOT_CONSTANT_ERROR 218					//�ǳ���
#define DUPLICATE_DEFINATION_ERROR 300			//�ظ������ʶ��
#define UNDEFINED_IDENTITY_ERROR 301			//δ�����ʶ��
#define CANNOT_ASSIGN_IDENTITY_ERROR 302		//���ܸ�ֵ��ʶ��
#define NOT_ARRAY_ERROR 303						//������
#define NOT_FUNCTION_ERROR 304					//�Ǻ���
#define INDEX_TYPE_ERROR 305					//�±����ʹ���
#define INDEX_OUTOFRANGE_ERROR 306				//�±�Խ��
#define CANNOT_GETVALUE_IDENTITY_ERROR 307		//����ȡֵ��ʶ��
#define UNMATCHED_TYPE_ERROR 308				//���Ͳ�ƥ��
#define UNMATCHED_PARA_NUM_ERROR 309			//����������ƥ��
#define UNMATCHED_PARA_TYPE_ERROR 310			//�������Ͳ�ƥ��
#define MISSING_RETURN_VALUE_ERROR 311			//ȱʧ����ֵ
#define FUNC_RETURN_VALUE_ERROR	312				//�������ؿ�ֵ
#define UNMATCHED_RETURN_TYPE_ERROR 313			//�����������Ͳ�ƥ��

#define LEADING_ZERO_WARNING 100				//�޷�������ǰ����
#define ASSIGN_INTTOCHAR_WARNING 300			//���͸�ֵ�ַ���
#define MAY_MISSING_RETURN_VALUE_WARNING 301	//����ȱʧ����ֵ
#define PROC_RETURN_VALUE_WARNING 302			//���̷��طǿ�ֵ

void Error(int code);
void Warning(int code);

void SkipConstDefine();
void SkipVarDefine();
void SkipFuncDeclare();
void SkipParaTable();
void SkipStatement();
void SkipFactor();