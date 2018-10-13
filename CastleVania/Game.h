#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Input/KeyHandler.h"
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"
#include "WindowUtil.h"
#include "Input/DirectInput.h"

class DirectInput;

class Game
{
protected:

	WindowUtil* window;
	Direct3DManager* direct3D;
	DirectInput* directInput;
	KeyHandler* keyHandler;
	HWND hWnd;

public:

	Game();
	void virtual Init(HINSTANCE hInstance, int nCmdShow);
	void virtual Update();
	void virtual Render();
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	int Run();

	Simon* simon;

	~Game();
};