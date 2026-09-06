#pragma once

#include "Windows.h"
#include <d3d9.h>
#include "imgui.h"
#include "classes.h"

bool CreateOverlayWindow();
bool CreateDevice();
ImGuiIO& InitOverlay();
void Cleanup();

void BeginImGuiFrame(ImGuiIO& io);
void EndImGuiFrame();
void DrawMenu(Player& localPlayer);

void UpdateRenderDimensions();
bool isGameMinimized();
void HandleWindowMessages(MSG& msg);
bool HandleDeviceReset(int& lastWidth, int& lastHeight);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);