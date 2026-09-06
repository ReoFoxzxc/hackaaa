#pragma once
#include "vec.h"


bool WorldToScreen(const Vec3& world, Vec2& screen, float* m, int width, int height);

Vec2 CalcAimAngles(const Vec3& from, const Vec3& to);

template<typename T>
T clamp(T val, T min, T max) {
    return (val < min) ? min : (val > max) ? max : val;
}