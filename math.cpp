#include "math.h"
#include "globals.h"
#include <cmath>

bool WorldToScreen(const Vec3& world, Vec2& screen, float* m, int width, int height) {
    // Matrix is column-major: index as [row + col * 4]
    float clipX = world.x * m[0] + world.y * m[4] + world.z * m[8] + m[12];
    float clipY = world.x * m[1] + world.y * m[5] + world.z * m[9] + m[13];
    float clipW = world.x * m[3] + world.y * m[7] + world.z * m[11] + m[15];

    if (clipW < 0.001f) return false;

    float ndcX = clipX / clipW;
    float ndcY = clipY / clipW;

    screen.x = (width / 2.0f) + (ndcX * width / 2.0f);
    screen.y = (height / 2.0f) - (ndcY * height / 2.0f);

    return true;
}

Vec2 NormalizeAngles(Vec2 angle) {
    while (angle.x > 360.0f) angle.x -= 360.0f;
    while (angle.x < 0.0f) angle.x += 360.0f;

    if (angle.y > 85.0f) angle.y = 85.0f;
    if (angle.y < -85.0f) angle.y = -85.0f;

    return angle;
}

Vec2 CalcAimAngles(const Vec3& from, const Vec3& to) {
    Vec3 delta = to - from;
    float HorizontalDistance = sqrt(delta.x * delta.x + delta.y * delta.y);

    float yaw = atan2(delta.y, delta.x) * RadToDeg + 90.0f;
    float pitch = atan2(delta.z, HorizontalDistance) * RadToDeg;

    return NormalizeAngles(Vec2(yaw, pitch));
}