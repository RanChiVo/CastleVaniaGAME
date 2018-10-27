#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"
#include "WindowUtil.h"
#include "Input/DirectInput.h"

class Game
{
protected:

	WindowUtil* window;
	Direct3DManager* direct3D;
	DirectInput* directInput;
	DIDEVICEOBJECTDATA keyEvents[keyboard_buffer_size];
	
public:

	Game();
	void virtual init(HINSTANCE hInstance, int nCmdShow);
	void virtual update(float dt);
	void virtual renderObjects();
	void virtual loadResource();
	void virtual handleInput();

	void Render();
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	int Run();

	~Game();
};