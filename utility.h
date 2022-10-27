#pragma once
#include "framework.h"
#include "globals.h"

namespace utility
{
	DWORD GetProcId(const wchar_t* procName);
	HMODULE GetModuleHandleSafe(const wchar_t* pszModuleName);
	void Read(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void Write(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	uintptr_t PointerChain(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	uintptr_t PatternScanEx(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask);
	uintptr_t FindOffset(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask, uintptr_t base_offset, uintptr_t pre_base_offset, uintptr_t rindex, bool addRip = true);

}

static uintptr_t __cdecl I_beginthreadex(void* _Security, unsigned _StackSize, _beginthreadex_proc_type _StartAddress, void* _ArgList, unsigned _InitFlag, unsigned* _ThrdAddr) {
	return iat(_beginthreadex).get()(_Security, _StackSize, _StartAddress, _ArgList, _InitFlag, _ThrdAddr);
}