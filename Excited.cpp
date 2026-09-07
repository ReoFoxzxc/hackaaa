#include <iostream>
#include "utils.h"
#include "globals.h"
#include "render.h"
#include "playerManagement.h"
#include "functions.h"

#pragma comment(lib, "d3d9.lib")

int main()
{
    FreeConsole();

    if (!InitGame()) {
        std::cerr << "Failed to initialize the game" << std::endl;
        return -1;
    }

    ImGuiIO& io = InitOverlay();

    bool overlayVisible = false;

    while (msg.message != WM_QUIT)
    {
        HandleWindowMessages(msg);

        // Оставляем обновление размеров ДО ESP/W2S,
        // как было у тебя изначально.
        UpdateRenderDimensions();

        if (!HandleDeviceReset(lastWidth, lastHeight))
            break;

        io.DisplaySize = ImVec2(
            static_cast<float>(screenWidth),
            static_cast<float>(screenHeight)
        );

        const bool gameActive =
            isGameInForeground() &&
            !isGameMinimized();

        if (!gameActive)
        {
            if (overlayVisible)
            {
                ShowWindow(hwndOverlay, SW_HIDE);

                SetWindowPos(
                    hwndOverlay,
                    HWND_BOTTOM,
                    0, 0, 0, 0,
                    SWP_NOMOVE |
                    SWP_NOSIZE |
                    SWP_NOACTIVATE
                );

                overlayVisible = false;
            }

            Sleep(10);
            continue;
        }

        if (!overlayVisible)
        {
            ShowWindow(hwndOverlay, SW_SHOW);

            SetWindowPos(
                hwndOverlay,
                HWND_TOPMOST,
                0, 0, 0, 0,
                SWP_NOMOVE |
                SWP_NOSIZE |
                SWP_NOACTIVATE
            );

            overlayVisible = true;
        }

        g_playerManagement.ReadLocalPlayer();

        auto* localPlayer = g_playerManagement.getLocalPlayer();

        if (!localPlayer || !localPlayer->isValidCheck())
        {
            Sleep(1);
            continue;
        }

        g_playerManagement.BuildPlayerList();

        BeginImGuiFrame(io);

        DrawESP(g_playerManagement.getPlayers());
        DrawFOV();
        DrawHP(g_playerManagement.getPlayers());
        DrawND(g_playerManagement.getPlayers());
        DrawSL(g_playerManagement.getPlayers());

        AimBot(
            g_playerManagement.getPlayers(),
            g_playerManagement.getLocalPlayerRef(),
            settings.AimBotFOVValue
        );

        NoRecoil();

        EndImGuiFrame();

        Sleep(1);
    }

    Cleanup();
    return 0;
}
