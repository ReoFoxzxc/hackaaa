#include "playerManagement.h"
#include "memory.h"
#include "classes.h"
#include "globals.h"
#include "math.h"

void PlayerManagement::BuildPlayerList() {
	players.clear();
	float viewMatrix[16]{};
	if (!RPM(OFFSET_VIEWMATRIX_BASE, viewMatrix)) {
		return;
	}

	int totalPlayers = RPM<int>(OFFSET_NUMPLAYERS);
	uintptr_t playerListPtr = static_cast<uintptr_t>(RPM<uint32_t>(OFFSET_ENTITYLIST));


	if (playerListPtr == 0 || totalPlayers <= 0 || totalPlayers > MAX_PLAYERS) {
		return;
	}

	int currentFrame = RPM<int>(OFFSET_CURRENT_FRAME);
	for (int i = 0; i < MAX_PLAYERS; i++) {
		uintptr_t entryAddress = playerListPtr + i * sizeof(uint32_t);
		uintptr_t playerPtr = static_cast<uintptr_t>(RPM<uint32_t>(entryAddress));

		if (!playerPtr) continue;

		Player p(playerPtr);

		if (!p.isValidCheck() || !p.isAliveCheck()) { continue; }

		if (!WorldToScreen(p.HeadPos(), p.screenHead, viewMatrix, screenWidth, screenHeight)) { continue; }
		if (!WorldToScreen(p.FootPos(), p.screenFeet, viewMatrix, screenWidth, screenHeight)) { continue; }

		p.isEnemy = p.isEnemyCheck(localPlayer);
		p.isVisible = p.isVisibleCheck(currentFrame);
		p.distance = p.Distance(localPlayer);
		p.ComputeBoxDimensions();
		p.aimDistance = Vec2{ (float)screenWidth / 2, float(screenHeight) / 2 }.Distance(p.screenHead);

		players.push_back(std::move(p));
		if ((int)players.size() >= totalPlayers - 1) {
			break;
		}
	}
}	

void PlayerManagement::ReadLocalPlayer() {
	Player localPlayer(OFFSET_LOCALPLAYER, true);
	if (!localPlayer.isValidCheck()) return;
	this->localPlayer = std::move(localPlayer);
}