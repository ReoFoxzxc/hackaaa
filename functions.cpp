#include "functions.h"

void DrawESP(const std::vector<Player>& players) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    for (const auto& player : players) {
        if (settings.ESP && player.isEnemy) {
            player.DrawBox(drawList);
        }
    }
}