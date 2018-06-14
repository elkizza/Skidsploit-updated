#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x1139548,// Updated
	PENVCHECK = 0x73cff7, // Updated
	LUA_GETFIELD = 0x743E40, // Updated
	LUA_SETFIELD = 0x745BD0, // Updated
	LUA_SETTOP = 0x745fa0, // Updated
	LUA_PUSHSTRING = 0x7451F0, // Updated
	LUA_PUSHNUMBER = 0x745160, // Updated
	LUA_PUSHVALUE = 0x7452B0, // Updated
	LUA_GETMETATABLE = 0x744110, // Updated
	LUA_PCALL = 0x744C10, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return (ScriptContext + 56 * 1 + 164) ^ *(DWORD *)(ScriptContext + 56 * 1 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
