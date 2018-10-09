#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Input/KeyEventHandler.h"
#include "GameObjects/Simon.h"

#define DIRECTINPUT_VERSION 0x0800

class Game
{
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = nullptr;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = nullptr;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = nullptr;
	LPD3DXSPRITE spriteHandler = nullptr;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];
	LPKEYEVENTHANDLER keyHandler;
	DIDEVICEOBJECTDATA keyEvents[keyboard_buffer_size];

public:

	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Init(HINSTANCE hInstance, int nCmdShow);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	void Render();
	int Run();

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	Simon* simon;

	~Game();
};