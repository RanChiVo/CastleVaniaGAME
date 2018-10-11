#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Input/KeyEventHandler.h"
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"

#define DIRECTINPUT_VERSION 0x0800

class Game
{
protected:

	WindowUtil* window;
	Direct3DManager * direct3D;
	HWND hWnd;

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];
	LPKEYEVENTHANDLER keyHandler;
	DIDEVICEOBJECTDATA keyEvents[keyboard_buffer_size];

public:

	Game();
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void virtual Init(HINSTANCE hInstance, int nCmdShow);
	void virtual Update();
	void virtual Render();

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	int Run();

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	Simon* simon;

	~Game();
};