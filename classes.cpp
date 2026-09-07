#include "classes.h"
#include "memory.h"


Player::Player(uintptr_t playerPtr) {
    if (playerPtr == 0) return;
    auto temp = std::make_unique<PlayerStruct>();
    if (!RPM(playerPtr, *temp)) return;
    ptr = temp.get();
    internalStruct = std::move(temp);
    address = playerPtr;
}

Player::Player(uintptr_t offset, bool isOffset) {
    if (!isOffset) return;
    uint32_t ptr32 = RPM<uint32_t>(offset);
    uintptr_t playerPtr = static_cast<uintptr_t>(ptr32);
    if (playerPtr == 0) return;
    auto temp = std::make_unique<PlayerStruct>();
    if (!RPM(playerPtr, *temp)) return;
    ptr = temp.get();
    internalStruct = std::move(temp);
    address = playerPtr;
}

Player::Player(Player&& other) noexcept {
    internalStruct = std::move(other.internalStruct);
    ptr = internalStruct.get();
    address = other.address;
    screenHead = other.screenHead;
    screenFeet = other.screenFeet;
    isEnemy = other.isEnemy;
    isVisible = other.isVisible;
    distance = other.distance;
    boxHeight = other.boxHeight;
    boxWidth = other.boxWidth;
    aimDistance = other.aimDistance;

    other.ptr = nullptr;
    other.address = 0;
}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        internalStruct = std::move(other.internalStruct);
        ptr = internalStruct.get();
        address = other.address;
        screenHead = other.screenHead;
        screenFeet = other.screenFeet;
        isEnemy = other.isEnemy;
        isVisible = other.isVisible;
        distance = other.distance;
        boxHeight = other.boxHeight;
        boxWidth = other.boxWidth;
        aimDistance = other.aimDistance;
    }
    return *this;
}

PlayerStruct* Player::operator->() const {
    return ptr;
}

PlayerStruct& Player::operator*() const {
    return *ptr;
}

bool Player::isValidCheck() const {
    return ptr != nullptr;
}

bool Player::isAliveCheck() const {
    return ptr && ptr->health > 0;
}

int Player::getTeam() const {
    return ptr ? (ptr->state & 1) : -1;
}

bool Player::isVisibleCheck(int currentFrame) const {
    return isValidCheck() && ptr->lastVisibleFrame >= currentFrame;
}

bool Player::isEnemyCheck(const Player& localPlayer) const {
    return isValidCheck() && ((ptr->state & 1) != (localPlayer->state & 1));
}

int Player::getHealth() const {
    return ptr ? ptr->health : 0;
}

float Player::getYaw() const {
    return ptr ? ptr->yaw : 0.f;
}

float Player::getPitch() const {
    return ptr ? ptr->pitch : 0.f;
}

const char* Player::getName() const {
    return ptr ? ptr->name : "";
}

Vec3 Player::HeadPos() const {
    return ptr->positionHead + Vec3(0.f, 0.f, 0.75f);
}

Vec3 Player::FootPos() const {
    return ptr->positionFeet;
}

float Player::Distance(const Player& other) const {
    return this->HeadPos().Distance(other.HeadPos());
}

void Player::setHealth(int value) const {
    if (address) {
        WPM<int>(address + 0xEC, value);
    }
}

ImVec2 Player::getBoxTopLeft() const {
    return ImVec2(screenHead.x - boxWidth / 2, screenHead.y);
}

ImVec2 Player::getBoxBottomRight() const {
    return ImVec2(screenHead.x + boxWidth / 2, screenFeet.y);
}

ImU32 Player::getBoxColor() const {
    if (isEnemy) {
        return isVisible ? IM_COL32(255, 0, 0, 255) : IM_COL32(255, 255, 0, 255);
    }
    else {
        return isVisible ? IM_COL32(0, 0, 255, 255) : IM_COL32(0, 255, 255, 255);
    }
}

void Player::ComputeBoxDimensions() {
    boxHeight = screenFeet.y - screenHead.y;
    boxWidth = boxHeight / 2.0f;

}

void Player::DrawBox(ImDrawList* drawList, float rounding, float thickness) const {
    drawList->AddRect(getBoxTopLeft(), getBoxBottomRight(), getBoxColor(), rounding, 0, thickness);
}

void Player::DrawTextAboveBox(ImDrawList* drawList, const std::string& text, float yOffset, ImU32 Color) const {
    ImVec2 topLeft = getBoxTopLeft();
    ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
    ImVec2 pos = ImVec2(screenHead.x - textSize.x / 2.0f, topLeft.y + yOffset);
    drawList->AddText(pos, Color, text.c_str());
}

void Player::DrawHealthBar(ImDrawList* drawList) const {

}

void Player::DrawDistance(ImDrawList* drawList, ImU32 color) const {

}

void Player::DrawName(ImDrawList* drawList) const {

}

void Player::DrawNameAndDistance(ImDrawList* drawList) const {

}

void Player::DrawSnapline(ImDrawList* drawList) const {

}