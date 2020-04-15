#pragma once
#include "WindowUtil.h"
#include "DebugOut/DebugOut.h"


class Direct3DManager
{
private: 
	static Direct3DManager* _instance;
	HWND hWnd;
	LPDIRECT3D9 d3d = nullptr;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = nullptr;
	LPDIRECT3DSURFACE9 backBuffer = nullptr;
	LPD3DXSPRITE spriteHandler = nullptr;			// Sprite helper library to help us draw 2D image on the ScreenBase 
	Direct3DManager();
	Viewport* viewport;

public:
	
	void init(WindowUtil *windowGame);
	void clearBackBuffer();
	void callPresent();
	
	Viewport* getViewport();
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	HWND gethWnd();

	static Direct3DManager* getInstance();
	~Direct3DManager();
};

