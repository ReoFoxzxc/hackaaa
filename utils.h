#pragma once
#include "Windows.h"
#include <tlhelp32.h>

DWORD getProcessID(const wchar_t* processName);
HANDLE OpenProcess(DWORD PID, const wchar_t* processName);
HWND FindGameWindow(DWORD PID);
bool InitGame();