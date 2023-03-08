#pragma once

#include <intrin.h>

extern "C"
{
	#pragma function(memset)
	void* __cdecl memset(void* dest, int value, size_t num)
	{
		__stosb(static_cast<unsigned char*>(dest), static_cast<unsigned char>(value), num);
		return dest;
	}

	#pragma function(memcpy)
	void* __cdecl memcpy(void* dest, const void* src, size_t num)
	{
		__movsb(static_cast<unsigned char*>(dest), static_cast<const unsigned char*>(src), num);
		return dest;
	}
}