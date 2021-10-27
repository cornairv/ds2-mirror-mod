#include "pch.h"
#include "util.h"
#include <algorithm>
#include <detours/detours.h>
#include "logger.h"

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

HRESULT PatchMem(void* instrAddr, void* data, size_t size)
{
	DWORD OldProtection;
	if (!VirtualProtect(instrAddr, size, PAGE_READWRITE, &OldProtection))
	{
		return E_FAIL;
	}
	memcpy(instrAddr, data, size);
	if (!VirtualProtect(instrAddr, size, OldProtection, &OldProtection))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT InjectCode(void* hookAddr, void* trampolineCode)
{
	DWORD trampolineMemSize;
	byte* trampolineMem = (byte*)DetourAllocateRegionWithinJumpBounds(hookAddr, &trampolineMemSize);
	if (trampolineMem == nullptr)
	{
		return E_FAIL;
	}
	byte* trampolineMemEnd = trampolineMem + trampolineMemSize;

	// copy trampoline code
	byte* currentSrc = (byte*)trampolineCode;
	byte* currentDst = trampolineMem;
	size_t trampolineSize = 0;
	while (*currentSrc != 0x90) // until NOP is reached
	{
		size_t instrSize = (byte*)DetourCopyInstruction(currentDst, (void**)&trampolineMemEnd, currentSrc, nullptr, nullptr) - currentSrc;
		if (instrSize == 0)
		{
			return E_FAIL;
		}
		currentSrc += instrSize;
		currentDst += instrSize;
		trampolineSize += instrSize;
	}

	// copy enough instructions to inject jmp
	byte jmpInstr[5];
	currentSrc = (byte*)hookAddr;
	size_t movedInstrsSize = 0;
	while (currentSrc - (byte*)hookAddr < sizeof(jmpInstr))
	{
		size_t instrSize = (byte*)DetourCopyInstruction(currentDst, (void**)&trampolineMemEnd, currentSrc, nullptr, nullptr) - currentSrc;
		if (instrSize == 0)
		{
			return E_FAIL;
		}
		currentSrc += instrSize;
		currentDst += instrSize;
		movedInstrsSize += instrSize;
		trampolineSize += instrSize;
	}

	// jmp back
	jmpInstr[0] = 0xe9;
	int* pJmpOffset = (int*)(jmpInstr + 1);
	long long jmpOffset64 = ((byte*)hookAddr + movedInstrsSize) - (trampolineMem + trampolineSize) - 1;
	*pJmpOffset = (int)jmpOffset64;
	if (PatchMem(currentDst, jmpInstr, sizeof(jmpInstr)) != S_OK)
	{
		return E_FAIL;
	}

	// inject jmp
	jmpOffset64 = trampolineMem - ((byte*)hookAddr + sizeof(jmpInstr));
	*pJmpOffset = (int)jmpOffset64;
	if (PatchMem(hookAddr, jmpInstr, sizeof(jmpInstr)) != S_OK)
	{
		return E_FAIL;
	}

	return S_OK;
}