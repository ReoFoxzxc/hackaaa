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


void AimBot(const std::vector<Player>& players, Player& localPlayer) {
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

    Vec2 aimAngles = CalcAimAngles(localPlayer.HeadPos(), best_target->HeadPos());
    WPM<float>(localPlayer.address + 0x034, aimAngles.x);
    WPM<float>(localPlayer.address + 0x038, aimAngles.y);
}