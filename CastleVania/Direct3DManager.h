#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "WindowUtil.h"


class Direct3DManager
{
private: 
	static Direct3DManager* _instance;
	HWND hWnd;
	LPDIRECT3D9 d3d = nullptr;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = nullptr;
	LPDIRECT3DSURFACE9 backBuffer = nullptr;
	LPD3DXSPRITE spriteHandler = nullptr;			// Sprite helper library to help us draw 2D image on the screen 

	Direct3DManager();

public:
	
	void init(WindowUtil *windowGame);
	void clearBackBuffer();
	void callPresent();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	HWND gethWnd();

	static Direct3DManager* getInstance();
	~Direct3DManager();
};
