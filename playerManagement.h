#pragma once
#include <vector>
#include "classes.h"


class PlayerManagement {
private:
	std::vector<Player> players;
	Player localPlayer;	
public:
	void BuildPlayerList();
	void ClearPlayerList() { players.clear(); }
	void ReadLocalPlayer();

	//getters

	const std::vector<Player>& getPlayers() const { return players; }
	Player* getLocalPlayer() { return &localPlayer; }
	Player& getLocalPlayerRef() { return localPlayer; }
};