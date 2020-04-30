#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"
#include "WindowUtil.h"
#include "Scene.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

class Game
{
protected:
	static Game * __instance;
	WindowUtil* window;
	Direct3DManager* direct3D;

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
	unordered_map<EntityID, LPSCENE> scenes;
	EntityID current_scene;
	Game();
public:
	static Game * GetInstance();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void InitKeyboard();
	void virtual init(HINSTANCE hInstance, int nCmdShow);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void virtual update(DWORD dt);
	void virtual Load(std::string gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(EntityID scene_id);
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