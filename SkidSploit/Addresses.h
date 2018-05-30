#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x1121698,// Updated
	PENVCHECK = 0x7385f7, // Updated
	LUA_GETFIELD = 0x73F4E0, // Updated
	LUA_SETFIELD = 0x741290, // Updated
	LUA_SETTOP = 0x741660, // Updated
	LUA_PUSHSTRING = 0x740880, // Updated
	LUA_PUSHNUMBER = 0x7407F0, // Updated
	LUA_PUSHVALUE = 0x740950, // Updated
	LUA_GETMETATABLE = 0x73F7B0, // Updated
	LUA_PCALL = 0x7402C0, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return(ScriptContext + 56 * 0 + 164) ^ *(DWORD *)(ScriptContext + 56 * 0 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}