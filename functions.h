#pragma once
#include "classes.h"
#include "globals.h"
#include <vector>

void DrawESP(const std::vector<Player>& players);
void AimBot(const std::vector<Player>& players, Player& localPlayer, float fov);
void DrawFOV();