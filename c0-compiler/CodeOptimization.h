#pragma once

struct BaseBlock {
	int s;
	int t;
};

void DeleteInvalidCode();
void ConstantCombination();
void CommonSubexpressionElimination();
void AllocGlobalReg();
void AllocTempReg();
void ClearUnusedVar();

int Calc(int op, int op1, int op2);