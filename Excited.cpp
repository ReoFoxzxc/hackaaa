#include <iostream>
#include "utils.h"
#include "globals.h"
#include "render.h"
#include "playerManagement.h"
#include "functions.h"
#pragma comment(lib, "d3d9.lib")

int main()
{
    if (!InitGame()) {
        std::cerr << "Failed to initialize the game" << std::endl;
        return -1;
    }
    ImGuiIO& io = InitOverlay();


    while (msg.message != WM_QUIT) {
        HandleWindowMessages(msg);  
        UpdateRenderDimensions();

        if (!HandleDeviceReset(lastWidth, lastHeight)) {
            break;
        }

        io.DisplaySize = ImVec2(float(screenWidth), float(screenHeight));
        if (!isGameInForeground() || isGameMinimized()) {
            ShowWindow(hwndOverlay, SW_HIDE);
            SetWindowPos(hwndOverlay, HWND_BOTTOM, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            continue;
        }
        else {
            ShowWindow(hwndOverlay, SW_SHOW);
            SetWindowPos(hwndOverlay, HWND_TOPMOST, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
        bool KeyPressed = (GetAsyncKeyState(VK_INSERT) & 1);

        if (KeyPressed && !lastKeyState) {
            settings.showMenu = !settings.showMenu;
            UpdateOverlayInputMode(settings.showMenu);
        }

        lastKeyState = KeyPressed;
        g_playerManagement.ReadLocalPlayer();

        if (!g_playerManagement.getLocalPlayer()->isValidCheck()) continue;

        g_playerManagement.BuildPlayerList();

        BeginImGuiFrame(io);
        DrawMenu(g_playerManagement.getLocalPlayerRef());
        DrawESP(g_playerManagement.getPlayers());
        EndImGuiFrame();
    }
    Cleanup();
    return 0;
}

/*
фикс миниизации
чек фокус или нет
фикс после альтаба на 1 мс боты становятся !isVisible при движении камеры или движении игрока
*/