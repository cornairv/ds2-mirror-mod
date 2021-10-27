#pragma once

#include <limits>
#include <initializer_list>

template<typename T>
void swapBits(T& n, unsigned int bit1, unsigned int bit2)
{
	bool b1 = n & bit1;
	bool b2 = n & bit2;
	if (b1 != b2)
	{
		n ^= bit1;
		n ^= bit2;
	}
}

// avoid integer overflow when negating min value
template<typename T>
void safeNegate(T& n)
{
	if (n == std::numeric_limits<T>::min())
	{
		n++;
	}
	n *= -1;
	if (n == std::numeric_limits<T>::min() + 1)
	{
		n--;
	}
}

char my_tolower(char ch);

template<typename T>
T derefOffsets(void* ptr, std::initializer_list<long long> offsets, long long finalOFfset = 0)
{
	byte* addr = static_cast<byte*>(ptr);
	for (long long offset : offsets)
	{
		addr = *(byte**)(addr + offset);
	}
	return reinterpret_cast<T>(addr + finalOFfset);
}

// memory operations

void PatchCmp(void* InstrAddr);
HRESULT PatchMem(void* instrAddr, void* data, size_t size);
HRESULT InjectCode(void* hookAddr, void* trampolineCode);
