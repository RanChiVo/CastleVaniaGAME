#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Debug/DebugOut.h"

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
