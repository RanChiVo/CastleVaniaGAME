#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"
#include "WindowUtil.h"
#include "Input/DirectInput.h"

constexpr unsigned int ScreenBase_width = 640;
constexpr unsigned int ScreenBase_height = 480;
constexpr int max_frame_rate = 60;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)

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
	int Run();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);

	~Game();
};