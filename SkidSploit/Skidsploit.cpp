/*
	Windows Includes
*/

#include <Windows.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <istream>
#include <sstream>

/*
	User Includes
*/

#include "Lua.h"
#include "Functions.h"

using namespace std;

std::string Input() {
	std::string a;
getline(std::cin, a);
return a;
}

std::vector<std::string> split(std::string s) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

void GetService(std::string service)
{
	GetField(LuaState, LUA_GLOBALSINDEX, "game");
	GetField(LuaState, -1, "GetService");
	PushValue(LuaState, -2);
	PushString(LuaState, service.c_str());
	PCall(LuaState, 2, 1, 0);
}

void Console(char* title)
{
	DWORD nothing;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &nothing);
	*(BYTE*)(&FreeConsole) = 0xC3;

	AllocConsole();
	SetConsoleTitleA(title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
}

/* 
	Scanning Stuff
*/

bool Compare(const BYTE *pData, const BYTE *bMask, const char *szMask) {
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask) return 0;
	return (*szMask) == NULL;
}

DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *szMask) {
	for (int i = 0; i < (int)dwLen; i++)
		if (Compare((BYTE*)(dwAddress + (int)i), bMask, szMask))  return (int)(dwAddress + i);
	return 0;
}

int Scan(DWORD mode, char* content, char* mask, DWORD Offset = 0) {
	DWORD PageSize;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	PageSize = si.dwPageSize;
	MEMORY_BASIC_INFORMATION mi;
	for (DWORD lpAddr = (DWORD)GetModuleHandleA(0) + Offset; lpAddr < 0x7FFFFFFF; lpAddr += PageSize) {
		DWORD vq = VirtualQuery((void*)lpAddr, &mi, PageSize);
		if (vq == ERROR_INVALID_PARAMETER || vq == 0) break;
		if (mi.Type == MEM_MAPPED) continue;
		if (mi.Protect == mode) {
			int addr = FindPattern(lpAddr, PageSize, (PBYTE)content, mask);
			if (addr != 0) {
				return addr;
			}
		}
	}
}

void PrintConsole(string Text) {
	std::cout << Text << endl;
}

void ScanScript() {
	DWORD ScriptContextAddress = aslr(SCRIPTCONTEXT);
	ScriptContext = (DWORD)(Scan(PAGE_READWRITE, (char*)&ScriptContextAddress, "xxxx", 0x401000));
}

void ScanState() {
	LuaState = GlobalState(ScriptContext);
}

void ScanData() {
	DataModel = GetParent(ScriptContext);
}

void ScanWorkspace() {
	Workspace = FindFirstClass(DataModel, "Workspace");
}

void ScanLighting() {
	Lighting = FindFirstClass(DataModel, "Lighting");
}

void ScanPlayers() {
	Players = FindFirstClass(DataModel, "Players");
}

void ExecuteCommand(std::string Command) {
			std::vector<std::string> In = split(Command);
			
			if (In.at(0) == "cmds") {
				try {
					
					std::cout << "cmds - Prints the commands" << endl;
					std::cout << "ff <Player> - Gives a forcefield to the specified player" << endl;
					std::cout << "unff <Player> - Removes a forcefield from the specified player" << endl;
					std::cout << "fire <Player> - Gives fire to the specified player" << endl;
					std::cout << "unfire <Player> - Removes fire from the specified player" << endl;
					std::cout << "smoke <Player> - Gives smoke to the specified player" << endl;
					std::cout << "unsmoke <Player> - Removes smoke from the specified player" << endl;
					std::cout << "sparkles <Player> - Gives sparkles to the specified player" << endl;
					std::cout << "unsparkles <Player> - Removes sparkles from the specified player" << endl;
					std::cout << "god <Player> - Gives the specified player LOTS of health" << endl;
					std::cout << "kill <Player> - Kills the specified player" << endl;
					std::cout << "punish <Player> - Removes the specified players character model frm the game" << endl;
					std::cout << "unpunish <Player> - Adds the specified players character model back to the game" << endl;
					std::cout << "walkspeed <Player> <Number> - Changes the specified players walkspeed" << endl;
					
					
				}
				catch (std::exception) {
					std::cout << "Could not execute command Cmds." << endl;
				}
			}

			if (In.at(0) == "fire") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "Fire");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 1, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "Fire");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 1, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command fire." << endl;
				}
			}

			else if (In.at(0) == "smoke") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "Smoke");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 1, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "Smoke");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 1, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command Smoke." << endl;
				}
			}

			else if (In.at(0) == "sparkles") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "Sparkles");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 1, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "Sparkles");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 1, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command Sparkles." << endl;
				}
			}

			else if (In.at(0) == "ff") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "ForceField");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 0, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "Instance");
						GetField(LuaState, -1, "new");
						PushString(LuaState, "ForceField");
						PushValue(LuaState, -4);
						PCall(LuaState, 2, 0, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command Forcefield." << endl;
				}
			}

			else if (In.at(0) == "god") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Humanoid");
						PushNumber(LuaState, HUGE_VAL);
						SetField(LuaState, -2, "MaxHealth");
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Humanoid");
						PushNumber(LuaState, HUGE_VAL);
						SetField(LuaState, -2, "MaxHealth");
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command god." << endl;
				}
			}

			else if (In.at(0) == "kill") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Humanoid");
						PushNumber(LuaState, 0);
						SetField(LuaState, -2, "Health");
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Humanoid");
						PushNumber(LuaState, 0);
						SetField(LuaState, -2, "Health");
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command kill." << endl;
				}
			}

			else if (In.at(0) == "unff") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "ForceField");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "ForceField");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command unff." << endl;
				}
			}

			else if (In.at(0) == "unfire") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetField(LuaState, -1, "Fire");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "Fire");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command unfire." << endl;
				}
			}

			else if (In.at(0) == "unsparkles") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetField(LuaState, -1, "Sparkles");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "Sparkles");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command unsparkles." << endl;
				}
			}

			else if (In.at(0) == "unsmoke") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");
						GetField(LuaState, -1, "Torso");

						GetField(LuaState, -1, "Smoke");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "Smoke");
						GetField(LuaState, -1, "remove");
						PushValue(LuaState, -2);
						PCall(LuaState, 1, 0, 0);
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command unsmoke." << endl;
				}
			}

			else if (In.at(0) == "punish") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Lighting");
						SetField(LuaState, -3, "Parent");

					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Lighting");
						SetField(LuaState, -3, "Parent");
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command punish." << endl;
				}
			}

			else if (In.at(0) == "punish") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Lighting");
						SetField(LuaState, -3, "Parent");

					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Lighting");
						SetField(LuaState, -3, "Parent");
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command punish." << endl;
				}
			}


			else if (In.at(0) == "unpunish") {
				try {
					if (In.at(1) == "me") {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Workspace");
						SetField(LuaState, -3, "Parent");

					}
					else {
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Workspace");
						SetField(LuaState, -3, "Parent");
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command unpunish." << endl;
				}
			}

			else if (In.at(0) == "walkspeed") {
				try {
					if (In.at(1) == "me") {
						float Number = atof(In.at(2).c_str());
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, "LocalPlayer");
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "Humanoid");
						PushNumber(LuaState, Number);
						SetField(LuaState, -2, "WalkSpeed");

					}
					else {
						float Number = atof(In.at(2).c_str());
						GetGlobal(LuaState, "game");
						GetField(LuaState, -1, "Players");
						GetField(LuaState, -1, In.at(1).c_str());
						GetField(LuaState, -1, "Character");

						GetField(LuaState, -1, "Humanoid");
						PushNumber(LuaState, Number);
						SetField(LuaState, -2, "WalkSpeed");
					}
				}
				catch (std::exception) {
					std::cout << "Could not execute command walkspeed." << endl;
				}
			}
		}



void ExecCmd(std::string Command) {
	try {
		ExecuteCommand(Command);
	}
	catch (...) {

	}
}



void Initialize(string Command) {
	Console("SkidSploit");
	std::cout << "Scanning Script Context..." << endl;
	ScanScript();
	std::cout << "Done!" << endl;
	std::cout << "Scanning LuaState..." << endl;
	ScanState();
	std::cout << "Done!" << endl;
	std::cout << "Scanning DataModel" << endl;
	ScanData();
	std::cout << "Done!" << endl;
	std::cout << "Scanning Workspace..." << endl;
	ScanWorkspace();
	std::cout << "Done!" << endl;
	std::cout << "Scanning Lighting..." << endl;
	ScanLighting();
	std::cout << "Done!" << endl;
	std::cout << "Scanning Players..." << endl;
	ScanPlayers();
	std::cout << "Done!" << endl;
	std::cout << "Scanning Complete!" << endl;

	std::cout << "----------------------------------------------------------" << endl;
	std::cout << "ScriptContext: " << ScriptContext << endl;
	std::cout << "LuaState: " << LuaState << endl;
	std::cout << "Workspace: " << Workspace << endl;
	std::cout << "Lighting: " << Lighting << endl;
	std::cout << "Players: " << Players << endl;
	std::cout << "----------------------------------------------------------" << endl;

	std::cout << "----------------------------------------------------------" << endl;
	std::cout << "Type cmds to get a list of commands!" << endl;
	std::cout << "Updated bye elkizza on verm" << endl;
	std::cout << "----------------------------------------------------------" << endl;

	do {
		try {
			std::string inputs = Input();
			ExecCmd(inputs);
		}
		catch (std::exception) {
			std::cout << "Their was a error executing this command!" << endl;
		}
	} while (true);
}

int __stdcall DllMain(HMODULE a, DWORD b, void* c) {
	if (b == 1) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, 0, 0, 0);
	}
	return TRUE;
}