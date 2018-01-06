#include "stdafx.h"

extern Identity global[GlobalSize], local[LocalSize];
extern int gsize, lsize;

extern Identity* current;

unsigned int Hash(char *str);

Identity* Search(char name[], int code) {
	unsigned int hash = Hash(name);
	if (code & 1)
		if (current != NULL)
			for (int i = current->l; i < current->r; i++)
				if (local[i].hash == hash)
					if (strcmp(local[i].name, name) == 0)
						return &local[i];
	if (code & 2)
		for (int i = 0; i < gsize; i++)
			if (global[i].hash == hash)
				if (strcmp(global[i].name, name) == 0)
					return &global[i];
	return NULL;
}

Identity* AddConst(char name[], int type, int value, bool isglobal) {
	if (name[0] == '$') {
		if (current != NULL)
			for (int i = current->l; i < current->r; i++)
				if (local[i].kind == CONSTANT && local[i].type == type && local[i].value == value)
					return &local[i];
		for (int i = 0; i < gsize; i++)
			if (global[i].kind == CONSTANT && global[i].type == type && global[i].value == value)
				return &global[i];
	}
	if (isglobal) {
		if (Search(name, 2) != NULL) {
			Error(DUPLICATE_DEFINATION_ERROR);
			return NULL;
		}
		strcpy_s(global[gsize].name, name);
		global[gsize].kind = CONSTANT;
		global[gsize].type = type;
		global[gsize].value = value;
		global[gsize].isglobal = true;
		global[gsize++].hash = Hash(name);
		return &global[gsize - 1];
	}
	else {
		if (Search(name, 1) != NULL) {
			Error(DUPLICATE_DEFINATION_ERROR);
			return NULL;
		}
		strcpy_s(local[lsize].name, name);
		local[lsize].kind = CONSTANT;
		local[lsize].type = type;
		local[lsize].value = value;
		local[lsize].isglobal = false;
		local[lsize++].hash = Hash(name);
		if (current != NULL)current->r++;
		return &local[lsize - 1];
	}
}

Identity* AddVar(char name[], int type, bool isglobal) {
	if (isglobal) {
		if (Search(name, 2) != NULL) {
			Error(DUPLICATE_DEFINATION_ERROR);
			return NULL;
		}
		strcpy_s(global[gsize].name, name);
		global[gsize].kind = VARIABLE;
		global[gsize].type = type;
		global[gsize].value = type == INT ? INT_INIT : CHAR_INIT;
		global[gsize].isglobal = true;
		global[gsize++].hash = Hash(name);
		return &global[gsize - 1];
	}
	else {
		if (Search(name, 1) != NULL) {
			Error(DUPLICATE_DEFINATION_ERROR);
			return NULL;
		}
		strcpy_s(local[lsize].name, name);
		local[lsize].kind = VARIABLE;
		local[lsize].type = type;
		local[lsize].value = type == INT ? INT_INIT : CHAR_INIT;
		local[lsize].isglobal = false;
		local[lsize++].hash = Hash(name);
		if (current != NULL)current->r++;
		return &local[lsize - 1];
	}
}

void AddPara(char name[], int type) {
	if (Search(name, 1) != NULL) {
		Error(DUPLICATE_DEFINATION_ERROR);
		return;
	}
	strcpy_s(local[lsize].name, name);
	local[lsize].kind = PARAMETER;
	local[lsize].type = type;
	local[lsize].isglobal = false;
	local[lsize++].hash = Hash(name);
	if (current != NULL)current->r++;
}

Identity* AddProc(char name[]) {
	if (Search(name, 2) != NULL) {
		Error(DUPLICATE_DEFINATION_ERROR);
		return NULL;
	}
	strcpy_s(global[gsize].name, name);
	global[gsize].kind = PROCEDURE;
	global[gsize].isglobal = true;
	global[gsize++].hash = Hash(name);
	return &global[gsize - 1];
}

Identity* AddFunc(char name[], int type) {
	if (Search(name, 2) != NULL) {
		Error(DUPLICATE_DEFINATION_ERROR);
		return NULL;
	}
	strcpy_s(global[gsize].name, name);
	global[gsize].kind = FUNCTION;
	global[gsize].type = type;
	global[gsize].isglobal = true;
	global[gsize++].hash = Hash(name);
	return &global[gsize - 1];
}

void AddArray(char name[], int type, int size, bool isglobal) {
	if (isglobal) {
		if (Search(name, 2) != NULL) {
			Error(DUPLICATE_DEFINATION_ERROR);
			return;
		}
		strcpy_s(global[gsize].name, name);
		global[gsize].kind = ARRAY;
		global[gsize].type = type;
		global[gsize].size = size;
		global[gsize].value = type == INT ? INT_INIT : CHAR_INIT;
		global[gsize].isglobal = true;
		global[gsize++].hash = Hash(name);
	}
	else {
		if (Search(name, 1) != NULL) {
			Error(DUPLICATE_DEFINATION_ERROR);
			return;
		}
		strcpy_s(local[lsize].name, name);
		local[lsize].kind = ARRAY;
		local[lsize].type = type;
		local[lsize].size = size;
		local[lsize].value = type == INT ? INT_INIT : CHAR_INIT;
		local[lsize].isglobal = false;
		local[lsize++].hash = Hash(name);
		if(current != NULL)current->r++;
	}
}

unsigned int Hash(char *str) {
	unsigned int seed = 31;
	unsigned int hash = 0;
	while (*str)
		hash = hash * seed + (*str++);
	return (hash & 0x7fffffff);
}