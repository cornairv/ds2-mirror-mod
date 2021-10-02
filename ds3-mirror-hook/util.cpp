#include "pch.h"
#include "util.h"
#include <algorithm>

char my_tolower(char ch)
{
	return static_cast<char>(tolower(static_cast<unsigned char>(ch)));
}

// patch CMP instruction to always be true
void PatchCmp(void* instrAddr)
{
	byte instr[] = {0x39, 0xc0};
	PatchMem(instrAddr, instr, sizeof(instr));
}

void PatchMem(void* instrAddr, void* data, int size)
{
	DWORD OldProtection;
	VirtualProtect(instrAddr, size, PAGE_READWRITE, &OldProtection);
	memcpy(instrAddr, data, size);
	VirtualProtect(instrAddr, size, OldProtection, &OldProtection);
}