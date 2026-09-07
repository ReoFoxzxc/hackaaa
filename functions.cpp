#include "functions.h"
#include "memory.h"
#include "math.h"



void DrawESP(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    for (const auto& player : players) {
        if (player.isEnemy) { player.DrawBox(drawList); }
    }
}


void DrawFOV() {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    ImVec2 center = ImVec2(
        static_cast<float>(screenWidth) / 2.0f,
        static_cast<float>(screenHeight) / 2.0f
    );

    float radius = 250.0f;
    ImU32 color = IM_COL32(255, 0, 0, 255); // Red color (RGBA)


    drawList->AddCircle(center, radius, color);
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