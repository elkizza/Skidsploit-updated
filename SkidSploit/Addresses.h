#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x1397508,// Updated
	PENVCHECK = 0x774ce7, // Updated
	LUA_GETFIELD = 0x77BC20, // Updated
	LUA_SETFIELD = 0x77D9C0, // Updated
	LUA_SETTOP = 0x77dd90, // Updated
	LUA_PUSHSTRING = 0x77CFD0, // Updated
	LUA_PUSHNUMBER = 0x77cf40, // Updated
	LUA_PUSHVALUE = 0x77D0A0, // Updated
	LUA_GETMETATABLE = 0x77BEF0, // Updated
	LUA_PCALL = 0x77C9F0, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return (ScriptContext + 56 * 1 + 164) + *(DWORD *)(ScriptContext + 56 * 1 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
