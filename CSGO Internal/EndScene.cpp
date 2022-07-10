#include "EndScene.h"
#include "globals.h"
#include "menu.h"
#include "esp.h"

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

// to set the size of the window n' what not
bool bESPInit = false;
ImVec2 vecESPSize = {0, 0};

IDirect3DDevice9* g_pDevice = nullptr;
HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice)
{
	if (!g_pDevice) g_pDevice = pDevice;
	if (!bInitialized) Initialize(pDevice);

	if (GetAsyncKeyState(VK_INSERT) & 1) bDrawMenu = !bDrawMenu;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	int scrw, scrh;
	I::IEngineClient->GetScreenSize(scrw, scrh);

	if (vecESPSize.x != scrw || vecESPSize.y != scrh)
	{
		vecESPSize = { scrw + 20.f, scrh + 20.f };

		// -10px to fix the clipping of the ESP
		ImGui::SetNextWindowPos({ -10.f, -10.f });

		// +20px to compensate
		ImGui::SetNextWindowSize(vecESPSize);
	}
	ImGui::Begin("##ESP_PANEL", (bool*)0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
	{
		//I::IEngineClient->WorldToScreenMatrix() = ESP::W2SMatrix;

		ESP::DrawVisuals();
	}
	ImGui::End();

	if (bDrawMenu)
		DrawMenu();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}