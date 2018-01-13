#pragma once

struct BaseBlock {
	int s;
	int t;
};

void DeleteInvalidCode();
void CommonSubexpressionElimination();
void AllocGlobalReg();
void AllocTempReg();