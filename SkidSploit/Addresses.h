#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x1169688,// Updated
	PENVCHECK = 0x723a87, // Updated
	LUA_GETFIELD = 0x72A970, // Updated
	LUA_SETFIELD = 0x72C6A0, // Updated
	LUA_SETTOP = 0x72ca70, // Updated
	LUA_PUSHSTRING = 0x72BCD0, // Updated
	LUA_PUSHNUMBER = 0x72bc40, // Updated
	LUA_PUSHVALUE = 0x72BD90, // Updated
	LUA_GETMETATABLE = 0x72AC30, // Updated
	LUA_PCALL = 0x72B710, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return (ScriptContext + 56 * 1 + 164) + *(DWORD *)(ScriptContext + 56 * 1 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
