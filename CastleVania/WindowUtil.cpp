#include <string>

#include "WindowUtil.h"

constexpr LPCWSTR WINDOW_CLASS_NAME = L"Castlevania";
constexpr LPCWSTR MAIN_WINDOW_TITLE = L"Castlevania";

constexpr bool FULLSCREEN = false;

LRESULT WindowUtil::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

WindowUtil::WindowUtil(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;
}

HWND WindowUtil::CreateGameWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			nullptr,
			nullptr,
			hInstance,
			nullptr);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}


WindowUtil::~WindowUtil()
{

}

WindowUtil::WindowUtil()
{
}
