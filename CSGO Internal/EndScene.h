#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

typedef HRESULT(__stdcall* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
extern tEndScene oEndScene;

extern IDirect3DDevice9* g_pDevice;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern WNDPROC oWndProc;
extern LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice);