/*
	User Includes
*/

#include "Retcheck.h"
#include "PenVCheck.h"
#include "Addresses.h"

#define LUA_GLOBALSINDEX -10002

#define GetGlobal(l,g)			 GetField(l, LUA_GLOBALSINDEX, g)

#define SetGlobal(L,n)            SetTop(L, -(n)-1)

typedef int(__fastcall*Typedef_GetField)(int a1, int a2, const char *a3);
Typedef_GetField GetField_Function = (Typedef_GetField)unprotect(aslr(LUA_GETFIELD));

typedef int(__fastcall*Typedef_SetField)(int a1, int a2, const char *a3);
Typedef_SetField SetField_Function = (Typedef_SetField)unprotect(aslr(LUA_SETFIELD));

typedef int(__cdecl*Typedef_SetTop)(int a1, int a2);
Typedef_SetTop SetTop_Function = (Typedef_SetTop)unprotect(aslr(LUA_SETTOP));

typedef int(__cdecl*Typedef_PushString)(int a1, const char *a2);
Typedef_PushString PushString_Function = (Typedef_PushString)aslr(LUA_PUSHSTRING);

typedef int(__stdcall*Typedef_PushNumber)(int a1, double a2);
Typedef_PushNumber PushNumber_Function = (Typedef_PushNumber)unprotect(aslr(LUA_PUSHNUMBER));

typedef int(__fastcall*Typedef_PushValue)(int a1, int a2);
Typedef_PushValue PushValue_Function = (Typedef_PushValue)unprotect(aslr(LUA_PUSHVALUE));

typedef int(__fastcall*Typedef_GetMetaTable)(int L, int idx);
Typedef_GetMetaTable GetMetaTable_function = (Typedef_GetMetaTable)unprotect(aslr(LUA_GETMETATABLE));

typedef int(__cdecl*Typedef_PCall)(int a1, int a2, int a3, int a4);
Typedef_PCall Pcall_Function = (Typedef_PCall)unprotect(aslr(LUA_PCALL));

void GetField(int a1, int a2, const char *a3) {
	GetField_Function(a1, a2, a3);
}

int SetFieldNoBypass(int a1, int a2, const char *a3) {
	return SetField_Function(a1, a2, a3);
}

void SetTop(int a1, int a2) {
	SetTop_Function(a1, a2);
}

void PushString(int a1, const char *a2) {
	PushString_Function(a1, a2);
}

void PushNumber(int a1, double a2) {
	PushNumber_Function(a1, a2);
}

void PushValue(int a1, int a2) {
	PushValue_Function(a1, a2);
}

bool GetMetaTable(int L, int idx) {
	return	GetMetaTable_function(L, idx);
}

void PCall(int a1, int a2, int a3, int a4) {
	BypassPen(); // Bypasses PenVCheck
	Pcall_Function(a1, a2, a3, a4);
	RestorePen(); // Restores PenVCheck
}

void SetField(int L, int idx, const char *k) {
	PushValue(L, idx);
	if (GetMetaTable(L, -1)) {
		GetField(L, -1, "__newindex");
		PushValue(L, -3);
		PushString(L, k);
		PushValue(L, -6);
		PCall(L, 3, 0, 0);
		SetGlobal(L, 3);
	}
	else {
		SetGlobal(L, 1);
		SetFieldNoBypass(L, idx, k);
	}
}
