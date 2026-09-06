#pragma once
#include "Windows.h"
#include "vec.h"

struct PlayerStruct {
    DWORD32 vftable;           // 0x000
    Vec3 positionHead;         // 0x004
    char pad1[0x028 - 0x010];   // 0x010 → 0x028
    Vec3 positionFeet;         // 0x028
    float yaw;                 // 0x034
    float pitch;               // 0x038
    char pad2[0x0D4 - 0x03C];  // 0x03C → 0x0D4
    int frameD4;               // 0x0D4
    int frameD8;               // 0x0D8
    char padXX[0x0E4 - 0x0DC]; // 0x0DC → 0x0E4
    int lastVisibleFrame;      // 0x0E4
    char padX[0x0EC - 0x0E8];  // 0x0E8 → 0x0EC
    int health;                // 0x0EC
    int armor;                 // 0x0F0
    char pad3[0x11C - 0x0F4];  // 0x0F4 → 0x11C
    int mag;                   // 0x11C
    char pad4[0x140 - 0x120];  // 0x120 → 0x140
    int ammo;                  // 0x140
    char pad5[0x1DC - 0x144];  // 0x144 → 0x1DC
    int frags;                 // 0x1DC
    char pad6[0x1E4 - 0x1E0];  // 0x1E0 → 0x1E4
    int deaths;                // 0x1E4 
    char pad7[0x205 - 0x1E8];  // 0x1E8 → 0x205
    char name[16];             // 0x205
    char pad8[0x30C - (0x205 + 16)];  // 0x215 → 0x30C
    int state;                 // 0x30C
    char pad11[0x33C - 0x310];
};