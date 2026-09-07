#pragma once
#include "classes.h"
#include "globals.h"
#include <vector>

void DrawESP(const std::vector<Player>& players);
void AimBot(const std::vector<Player>& players, Player& localPlayer, float fov);
void DrawHP(const std::vector<Player>& players);
void DrawDist(const std::vector<Player>& players);
void DrawFOV();
void DrawSL(const std::vector<Player>& players);
void DrawND(const std::vector<Player>& players);
void NoRecoil();