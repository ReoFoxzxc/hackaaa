	#include "globals.h"

	HWND hwndOverlay = nullptr;
	HWND hwndGame = nullptr;
	LPDIRECT3D9 pD3D = nullptr;
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	HANDLE hGame = nullptr;
	MSG msg = {};
	WNDCLASSEX wc = {};
	D3DPRESENT_PARAMETERS d3dpp = {};

	bool NoRecoilCurrentlyPatched = false;
	bool NoSpreadCurrentlyPatched = false;

	int screenWidth = 0;
	int screenHeight = 0;
	int lastWidth = 0;
	int lastHeight = 0;

	ExcitedSettings settings;

	PlayerManagement g_playerManagement;