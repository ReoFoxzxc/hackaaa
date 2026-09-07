#pragma once
#include <Windows.h>
#include <vector>

extern HANDLE hGame;

template <typename T>
bool RPM(uintptr_t address, T& outBuffer) {
	SIZE_T bytesRead = 0;
	return ReadProcessMemory(hGame, reinterpret_cast<LPCVOID>(address), &outBuffer, sizeof(T), &bytesRead)
		&& bytesRead == sizeof(T);
}

template<typename T>
T RPM(uintptr_t address) {
	T buffer{};
	ReadProcessMemory(hGame, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), nullptr);
	return buffer;
}

template <typename T>
bool WPM(uintptr_t address, T value) {
	SIZE_T bytesWritten = 0;
	return WriteProcessMemory(hGame, reinterpret_cast<LPVOID>(address), &value, sizeof(T), &bytesWritten)
		&& bytesWritten == sizeof(T);
}

inline void WPM(uintptr_t address, const BYTE* buffer, size_t size) {
	WriteProcessMemory(hGame, reinterpret_cast<LPVOID>(address), buffer, size, nullptr);
}

inline void NopMemory(uintptr_t address, size_t size) {
	std::vector<uint8_t> nopBytes(size, 0x90);
	WPM(address, nopBytes);
}