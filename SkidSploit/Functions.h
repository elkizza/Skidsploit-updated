#pragma once

#include <Windows.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cctype>

using namespace std;
std::string tolower(std::string str)
{
	std::string retn("");
	for (size_t i = 0; i < str.length(); i++)
	{
		int ascii = (int)str.at(i);
		if (ascii >= (int)'a' && ascii <= (int)'z')
			retn += (char)ascii;
		else
			retn += (char)(ascii + ((int)'a' - (int)'A'));
	}
	return retn;
}

int DataModel = 0;
int Workspace = 0;
int Players = 0;
int Lighting = 0;
int CurrentPlayer;
std::string *PlayerName;
bool IsFogBypassed = FALSE;


int GetParent(int Instance) {
	try {
		return *(int*)(Instance + 0x34);
	}
	catch (...) {
		printf("Couldn't get Parent!");
	}
}

const char* GetClass(int self)
{
	try {
		return (*(const char*(**)(void))(*(DWORD *)self + 16))();
	}
	catch (...) {
		printf("Couldn't get Class!");
	}
}


int FindFirstClasss(int Instance, const char* Name)
{
	try {
		DWORD StartOfChildren = *(DWORD*)(Instance + 0x2C);
		DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);

		for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8)
		{
			if (memcmp(GetClass(*(int*)i), Name, strlen(Name)) == 0)
			{
				return *(int*)i;
			}
		}
	}
	catch (...) {
		printf("Couldn't get FirstClass!");
	}
}

int FindFirstClass(int Instance, const char* ClassName) {
	if (Instance > 10000) {
		DWORD StartOfChildren = *(DWORD*)(Instance + 0x2C);
		if (StartOfChildren != 0) {
			DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);
			if (EndOfChildren != 0) {
				for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8) {
					try {
						if (memcmp(GetClass(*(int*)i), ClassName, strlen(ClassName)) == 0) {
							return *(int*)i;
						}
					}
					catch (std::exception) {
						printf("Couldn't get FirstClass!");
					}
					catch (...) {
						printf("Couldn't get FirstClass!");
					}
				}
			}
		}
	}
	return 0;
}

int GetService(const char* Name) {
	try {
		DWORD StartOfChildren = *(DWORD*)(DataModel + 0x2C);
		DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);

		for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8)
		{
			if (memcmp(GetClass(*(int*)i), Name, strlen(Name)) == 0)
			{
				return *(int*)i;
			}
		}

		return 0;
	}
	catch (...) {
		printf("Could not call GetService!");
	}
}

std::string* GetName(int Instance) {
	try {
		return (std::string*)(*(int*)(Instance + 0x28));
	}
	catch (...) {
		printf("Couldn't get Name!");
	}
}



int FindFirstChild_PartOf(int Instance, std::string Name) {
	try {
		DWORD StartOfChildren = *(DWORD*)(Instance + 0x2C);
		DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);
		for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8)
		{
			if (strstr(GetName(*(int*)i)->c_str(), Name.c_str()))
			{
				if (*(int*)i == 0)
				{

				}
				else {
					return *(int*)i;
				}
			}

		}
	}
	catch (...) {
		printf("Couldn't get FirstClassPart_Of!");
	}

}



int GetLocalPlayer(int Player) {
	try {
		return *(int*)(Player + 340);
	}
	catch (...) {
		printf("Couldn't Get Local Player!");
	}

}

std::string to_lowercase(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), std::ptr_fun<int, int>(std::tolower));
	return s;
}

int FindFirstPlayer(int Instance, std::string Name) {
	if (Instance > 10000) {
		DWORD StartOfChildren = *(DWORD*)(Instance + 0x2C);
		if (Name == "me") {
			return GetLocalPlayer(Players);
		}
		else {
			if (StartOfChildren != 0) {
				DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);
				if (EndOfChildren != 0) {
					for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8) {
						try {
							if (strstr(to_lowercase(*GetName(*(int*)i)).c_str(), to_lowercase(Name).c_str())) {
								return *(int*)i;
							}
						}
						catch (std::exception) {
							Sleep(1);
						}
						catch (...) {
							Sleep(1);
						}
					}
				}
			}
		}
	}
	return 0;
}

DWORD GetCharacterFromPlayer(DWORD player) {
	if (player > 1000) {
		//if ((int)(((int*)player) + 0x48) > 1000) {
		__try {
			return *(DWORD *)(player + 0x48);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return 0;
		}
		//}
	}
	return 0;
};


int GetCharacter(std::string Name) {
	if (Name != "") {
		if (Name == "me") {
			int Player = GetLocalPlayer(Players);
			if (Player != 0) {
				return GetCharacterFromPlayer(Player);
			}
			else {
				return 0;
			}
		}
		int Player = FindFirstPlayer(Players, Name);
		if (Player != 0) {
			return GetCharacterFromPlayer(Player);
		}
	}
	return 0;
}