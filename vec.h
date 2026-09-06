#pragma once
#include <cmath>

struct Vec2 {
	float x, y;

	Vec2(float x = 0, float y = 0) : x(x), y(y) {}

	float Distance(const Vec2& other) const {
		float dx = (x - other.x);
		float dy = (y - other.y);

		return sqrtf(dx * dx + dy * dy);
	}
};


struct Vec3 {
	float x, y, z;

	Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

	Vec3 operator-(const Vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	Vec3 operator+(const Vec3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	Vec3 operator*(const Vec3& other) const {
		return { x * other.x, y * other.y, z * other.z };
	}

	Vec3 operator/(const Vec3& other) const {
		return { x / other.x, y / other.y, z / other.z };
	}

	float Distance(const Vec3& other) const {
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;

		return sqrtf(dx * dx + dy * dy + dz * dz);
	}
};