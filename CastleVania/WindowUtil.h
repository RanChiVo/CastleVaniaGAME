#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "../CastleVania/ViewPort.h"

class WindowUtil
{
protected:

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HINSTANCE hInstance;
	HWND hWnd;
	int nCmdShow;
	int ScreenBaseWidth;
	int ScreenBaseHeight;
public:

	WindowUtil(HINSTANCE hInstance, int nCmdShow, int ScreenBaseWidth, int ScreenBaseHeight);
	HWND CreateGameWindow();
	~WindowUtil();
	WindowUtil();
};

typedef WindowUtil* windowUtil;
