#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x113A3C8,// Updated
	PENVCHECK = 0x73cc47, // Updated
	LUA_GETFIELD = 0x743B20, // Updated
	LUA_SETFIELD = 0x7458E0, // Updated
	LUA_SETTOP = 0x745cb0, // Updated
	LUA_PUSHSTRING = 0x744EE0, // Updated
	LUA_PUSHNUMBER = 0x744E50, // Updated
	LUA_PUSHVALUE = 0x744FC0, // Updated
	LUA_GETMETATABLE = 0x743DE0, // Updated
	LUA_PCALL = 0x744910, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return (ScriptContext + 56 * 1 + 164) - *(DWORD *)(ScriptContext + 56 * 1 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
