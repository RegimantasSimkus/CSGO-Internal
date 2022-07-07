#include "EndScene.h"
#include "globals.h"
#include "menu.h"

bool bDrawMenu = true;
WNDPROC oWndProc;
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (bDrawMenu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

#include <iostream>

tEndScene oEndScene = 0;
bool bInitialized = false;
void Initialize(IDirect3DDevice9* pDevice)
{
	// pretty scuffed
	D3DDEVICE_CREATION_PARAMETERS params;
	pDevice->GetCreationParameters(&params);
	std::cout << g_hWnd << "\n";
	std::cout << params.hFocusWindow << "\n";
	g_hWnd = params.hFocusWindow;
	oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG)WndProc);
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(pDevice);


	bInitialized = true;
}

IDirect3DDevice9* g_pDevice = nullptr;
HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice)
{
	if (!g_pDevice) g_pDevice = pDevice;
	if (!bInitialized) Initialize(pDevice);

	if (GetAsyncKeyState(VK_INSERT) & 1) bDrawMenu = !bDrawMenu;

	if (bDrawMenu)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

			DrawMenu();

		ImGui::EndFrame();

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return oEndScene(pDevice);
}