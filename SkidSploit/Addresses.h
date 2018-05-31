#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x1128D10,// Updated
	PENVCHECK = 0x7355d7, // Updated
	LUA_GETFIELD = 0x73C460, // Updated
	LUA_SETFIELD = 0x73E230, // Updated
	LUA_SETTOP = 0x73E610, // Updated
	LUA_PUSHSTRING = 0x73D830, // Updated
	LUA_PUSHNUMBER = 0x73d7a0, // Updated
	LUA_PUSHVALUE = 0x73D8F0, // Updated
	LUA_GETMETATABLE = 0x73C730, // Updated
	LUA_PCALL = 0x73d250, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return *(DWORD *)(ScriptContext + 56 * 1 + 164) - (ScriptContext + 56 * 1 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
