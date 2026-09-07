#include <iostream>
#include "utils.h"
#include "globals.h"

DWORD getProcessID(const wchar_t* processName) {
    PROCESSENTRY32W entry = { sizeof(entry) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(entry.szExeFile, processName) == 0) {
                DWORD pid = entry.th32ProcessID;
                CloseHandle(snapshot);
                return pid;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}

HANDLE OpenGameProcess(DWORD PID, const wchar_t* processName) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	if (hProcess == NULL) {
		return NULL;
	}

	return hProcess;
}

HWND FindGameWindow(DWORD PID) {
	HWND hwnd = 0;
	while ((hwnd = FindWindowEx(nullptr, hwnd, nullptr, nullptr))) {
		DWORD WindowPID = 0;
		GetWindowThreadProcessId(hwnd, &WindowPID);
		if (WindowPID == PID && IsWindowVisible(hwnd)) {
			return hwnd;
		}
	}
	return nullptr;
}

bool InitGame() {
	DWORD PID = getProcessID(PROCESS_NAME);
	if (!PID) {
		std::wcerr << L"[!] Failed to get process ID." << std::endl;
			return false;
	}

	hGame = OpenGameProcess(PID, PROCESS_NAME);
	if (!hGame) {
		std::wcerr << L"[!] Failed to open game handle." << std::endl;
		return false;
	}

	hwndGame = FindGameWindow(PID);
	if (!hwndGame) {
		std::wcerr << L"[!] Could not find game window." << std::endl;
		return false;
	}

	return true;
}