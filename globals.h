#pragma once
#include "Windows.h"
#include "playerManagement.h"
#include <d3d9.h>


// OFFSETS

constexpr uintptr_t OFFSET_LOCALPLAYER = 0x0058AC00;
constexpr uintptr_t OFFSET_NUMPLAYERS = 0x0058AC0C;
constexpr uintptr_t OFFSET_ENTITYLIST = 0x0058AC04;
constexpr uintptr_t OFFSET_CURRENT_FRAME = 0x0057F10C;
constexpr uintptr_t OFFSET_VIEWMATRIX_BASE = 0x0057DFD0;


// CONSTANTS

constexpr int MAX_PLAYERS = 32;
inline const wchar_t* PROCESS_NAME = L"ac_client.exe";
constexpr float RadToDeg = (180.0f / 3.14159265f);


// EXTERNS

extern HWND hwndOverlay;
extern HWND hwndGame;
extern LPDIRECT3D9 pD3D;
extern LPDIRECT3DDEVICE9 pDevice;
extern HANDLE hGame;
extern MSG msg;
extern WNDCLASSEX wc;
extern D3DPRESENT_PARAMETERS d3dpp;

extern int screenWidth;
extern int screenHeight;
extern int lastWidth;
extern int lastHeight;

extern bool lastKeyState;


//SETTINGS & CLASSES

struct ExcitedSettings {
	bool showMenu = false;
	bool ESP = false;
};

extern ExcitedSettings settings;
extern PlayerManagement g_playerManagement;