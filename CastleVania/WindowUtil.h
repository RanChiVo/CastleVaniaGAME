#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Debug/DebugOut.h"

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define FULLSCREEN	false
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

class WindowUtil
{
protected:

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HINSTANCE hInstance;
	HWND hWnd;
	int nCmdShow;
	int ScreenWidth;
	int ScreenHeight;

public:

	WindowUtil(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
	HWND CreateGameWindow();
	~WindowUtil();
	WindowUtil();
};

typedef WindowUtil* windowUtil;
