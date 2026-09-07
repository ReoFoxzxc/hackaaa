#pragma once
#include <memory>
#include <string>
#include "structs.h"
#include "Windows.h"
#include "imgui.h"


struct PlayerStruct;


class Player {
public:
	std::unique_ptr<PlayerStruct> internalStruct;
	PlayerStruct* ptr = nullptr;
	uintptr_t address = 0;

	Vec2 screenHead{};
	Vec2 screenFeet{};

	bool isEnemy = false;
	bool isVisible = false;
	float distance = 0.f;
	float boxHeight = 0.f;
	float boxWidth = 0.f;
	float aimDistance = 0.f;
	Player() = default;
	Player(uintptr_t playerPtr);
	Player(uintptr_t offset, bool isOffset);

	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	PlayerStruct* operator->() const;
	PlayerStruct& operator*() const;

	bool isValidCheck() const;
	bool isAliveCheck() const;
	int getTeam() const;
	bool isVisibleCheck(int currentFrame) const;
	bool isEnemyCheck(const Player& localPlayer) const;

	int getHealth() const;
	float getYaw() const;
	float getPitch() const;
	const char* getName() const;
	Vec3 HeadPos() const;
	Vec3 FootPos() const;
	float Distance(const Player& other) const;

	void setHealth(int value) const;

	ImVec2 getBoxTopLeft() const;
	ImVec2 getBoxBottomRight() const;
	ImU32 getBoxColor() const;
	void ComputeBoxDimensions();
	void DrawBox(ImDrawList* drawList, float rounding = 0.0f, float thickness = 1.0f) const;
	void DrawTextAboveBox(ImDrawList* drawList, const std::string &text, float yOffset, ImU32 color = IM_COL32(255, 255, 255, 255)) const;
	void DrawDistance(ImDrawList* drawList, float distance, ImU32 color = IM_COL32(255, 255, 255, 255)) const;
	void DrawHealthBar(ImDrawList* drawList) const;
	void DrawName(ImDrawList* drawList) const;
	void DrawNameAndDistance(ImDrawList* drawList, float distance, ImU32 color) const;
	void DrawSnapline(ImDrawList* drawList, ImU32 color) const;
};