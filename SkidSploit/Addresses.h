#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x11537A0,// Updated
	PENVCHECK = 0x748cc7, // Updated
	LUA_GETFIELD = 0x74FBF0, // Updated
	LUA_SETFIELD = 0x751970, // Updated
	LUA_SETTOP = 0x751D40, // Updated
	LUA_PUSHSTRING = 0x750F90, // Updated
	LUA_PUSHNUMBER = 0x750f00, // Updated
	LUA_PUSHVALUE = 0x751050, // Updated
	LUA_GETMETATABLE = 0x74FEB0, // Updated
	LUA_PCALL = 0x7509C0, // Updated
};

int GlobalState(DWORD ScriptContext) {
	return (ScriptContext + 56 * 1 + 164) - *(DWORD *)(ScriptContext + 56 * 1 + 164);
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
