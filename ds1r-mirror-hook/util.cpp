#include "pch.h"
#include "util.h"
#include <algorithm>

char my_tolower(char ch)
{
	return static_cast<char>(tolower(static_cast<unsigned char>(ch)));
}