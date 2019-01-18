#pragma once

/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>

int ScriptContext = 0;
int LuaState = 0;

enum rbxOffsets {
	SCRIPTCONTEXT = 0x17BB038,// Updated 18/01/2019
	//PENVCHECK = 0x774ce7, // Updated Not needed anymore due to roblox removing pcall's check
	LUA_GETFIELD = 0x77cc70, // Updated 18/01/2019
	LUA_SETFIELD = 0x77ea20, // Updated 18/01/2019
	LUA_SETTOP = 0x77edf0, // Updated 18/01/2019
	LUA_PUSHSTRING = 0x77e010, // Updated 18/01/2019
	LUA_PUSHNUMBER = 0x77df80, // Updated 18/01/2019
	LUA_PUSHVALUE = 0x77e0c0, // Updated 18/01/2019
	LUA_GETMETATABLE = 0x77cf40, // Updated 18/01/2019
	LUA_PCALL = 0x77da50, // Updated 18/01/2019
};


int GlobalState(DWORD ScriptContext) {
	int v39 = ScriptContext; // updated
        int v51 = 0; // updated 
	return v39 + 56 * v51 + 164 + *(DWORD *)(v39 + 56 * v51 + 164); // updated
}

//LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 *  + 164);
int aslr(int addr) {
	return (addr - 0x400000 + (DWORD)GetModuleHandle(0));
}
