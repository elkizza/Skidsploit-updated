/*
	Windows Includes
*/

#include <Windows.h>

void createFakeChain(DWORD* chain)
{
	chain[0] = -1;
	chain[6] = 0xB00B1E;
}

void restoreChain(DWORD* chain, DWORD next, DWORD unk)
{
	chain[0] = next;
	chain[6] = unk;
}