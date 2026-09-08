#include "functions.h"
#include "memory.h"
#include "math.h"



void DrawESP(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    drawList->Flags |= ImDrawListFlags_AntiAliasedLines;
    drawList->Flags |= ImDrawListFlags_AntiAliasedFill;
    drawList->Flags |= ImDrawListFlags_AntiAliasedLinesUseTex;

    for (const auto& player : players) {
        if (player.isEnemy) { player.DrawBox(drawList); }
    }
}


void DrawHP(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    drawList->Flags |= ImDrawListFlags_AntiAliasedLines;
    drawList->Flags |= ImDrawListFlags_AntiAliasedFill;
    drawList->Flags |= ImDrawListFlags_AntiAliasedLinesUseTex;


    for (const auto& player : players) {
        if (player.isEnemy) { player.DrawHealthBar(drawList); }
    }
}


void DrawDist(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    drawList->Flags |= ImDrawListFlags_AntiAliasedLines;
    drawList->Flags |= ImDrawListFlags_AntiAliasedFill;

    for (const auto& player : players) {
        if (player.isEnemy) {
            float distance = player.Distance(g_playerManagement.getLocalPlayerRef());
            player.DrawDistance(drawList, distance);
        }
    }
}


void DrawFOV() {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    drawList->Flags |= ImDrawListFlags_AntiAliasedLines;
    drawList->Flags |= ImDrawListFlags_AntiAliasedFill;
    drawList->Flags |= ImDrawListFlags_AntiAliasedLinesUseTex;

    ImVec2 center = ImVec2(
        static_cast<float>(screenWidth) / 2.0f,
        static_cast<float>(screenHeight) / 2.0f
    );

    float radius = 250.0f;
    ImU32 color = IM_COL32(255, 0, 0, 255); // Red color (RGBA)


    drawList->AddCircle(center, radius, color);
}


void DrawSL(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    drawList->Flags |= ImDrawListFlags_AntiAliasedLines;
    drawList->Flags |= ImDrawListFlags_AntiAliasedFill;
    drawList->Flags |= ImDrawListFlags_AntiAliasedLinesUseTex;

    ImU32 color = IM_COL32(255, 255, 255, 255);

    for (const auto& player : players) {
        if (player.isEnemy) {
            player.DrawSnapline(drawList, color);
        }
    }
}


void DrawND(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    drawList->Flags |= ImDrawListFlags_AntiAliasedLines;
    drawList->Flags |= ImDrawListFlags_AntiAliasedFill;
    drawList->Flags |= ImDrawListFlags_AntiAliasedLinesUseTex;

    ImU32 color = IM_COL32(255, 255, 255, 255);
    for (const auto& player : players) {
        if (player.isEnemy) {
            float distance = player.Distance(g_playerManagement.getLocalPlayerRef());
            player.DrawNameAndDistance(drawList, distance, color);
        }
    }
}


void AimBot(const std::vector<Player>& players, Player& localPlayer, float fov) {
    const Player* best_target = nullptr;
    float minAimDistance = FLT_MAX;

    for (const auto& player : players) {
        if (player.isEnemy && player.isVisible) {
            if (player.aimDistance < minAimDistance) {
                minAimDistance = player.aimDistance;
                best_target = &player;
            }
        }
    }

    if (best_target == nullptr) {
        return;
    }


    if (best_target->aimDistance <= fov) {
        Vec2 aimAngles = CalcAimAngles(localPlayer.HeadPos(), best_target->HeadPos());
        WPM<float>(localPlayer.address + 0x034, aimAngles.x);
        WPM<float>(localPlayer.address + 0x038, aimAngles.y);
    }
}


void NoSpread() {
    if (NoSpreadCurrentlyPatched) {
        return;
    }

    uintptr_t targetByteAddress = OFFSET_SPREAD + 1;
    BYTE jneOpcode = 0x85;

    WPM(targetByteAddress, &jneOpcode, sizeof(jneOpcode));

    NoSpreadCurrentlyPatched = true;
}


void NoRecoil() {
    if (NoRecoilCurrentlyPatched) {
        return;
    }

    NopMemory(OFFSET_RECOIL, 5);
    NopMemory(OFFSET_VELOCITY_X, 5);
    NopMemory(OFFSET_VELOCITY_Z, 5);
    NoRecoilCurrentlyPatched = true;
}

    /*
    
    BYTE originalRecoilBytes[5] = { 0xF3, 0x0F, 0x11, 0x56, 0x38 };
        WPM(OFFSET_RECOIL, originalRecoilBytes, sizeof(originalRecoilBytes));
        noRecoilCurrentlyPatched = false;
        
        */