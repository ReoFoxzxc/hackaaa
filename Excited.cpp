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
        if (!isGameMinimized()) {
            ShowWindow(hwndOverlay, SW_HIDE);
            continue;
        }
        else {
            ShowWindow(hwndOverlay, SW_SHOW);
        }
        bool KeyPressed = (GetAsyncKeyState(VK_INSERT) & 1);

        if (KeyPressed && !lastKeyState) {
            settings.showMenu = !settings.showMenu;
        }

        lastKeyState = KeyPressed;
        g_playerManagement.ReadLocalPlayer();
        g_playerManagement.BuildPlayerList();

        BeginImGuiFrame(io);
        DrawMenu(g_playerManagement.getLocalPlayerRef());
        DrawESP(g_playerManagement.getPlayers());
        EndImGuiFrame();
    }
}