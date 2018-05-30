/*
	Windos Includes
*/

#include <Windows.h>

/*
	User Includes
*/

#include "Addresses.h"


void BypassPen() {
	DWORD lpflOldProtect;
	VirtualProtect((void*)aslr(PENVCHECK), 5, PAGE_EXECUTE_READWRITE, &lpflOldProtect);
	//Changes protection to PAGE_EXECUTE_READWRITE so that we can modify the instruction
	memcpy((void*)aslr(PENVCHECK), "\xEB", 1);
	//Changes the instruction to an unconditional short jmp
	VirtualProtect((void*)aslr(PENVCHECK), 5, lpflOldProtect, &lpflOldProtect);
	//Restores original protection
}

void RestorePen() {
	DWORD lpflOldProtect;
	VirtualProtect((void*)aslr(PENVCHECK), 5, PAGE_EXECUTE_READWRITE, &lpflOldProtect);
	//Changes protection to PAGE_EXECUTE_READWRITE so that we can modify the instruction
	memcpy((void*)aslr(PENVCHECK), "\x74", 1);
	//Changes the instruction back to jz
	VirtualProtect((void*)aslr(PENVCHECK), 5, lpflOldProtect, &lpflOldProtect);
	//Restores original protection
}

/*
	Credit to tepig for the bypass
*/