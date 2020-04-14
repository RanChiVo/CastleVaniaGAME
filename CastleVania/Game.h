#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"
#include "WindowUtil.h"
#include "Input/DirectInput.h"
#include "Scene.h"

class Game
{
protected:
	static Game * __instance;
	WindowUtil* window;
	Direct3DManager* direct3D;
	DirectInput* directInput;
	DIDEVICEOBJECTDATA keyEvents[keyboard_buffer_size];
	unordered_map<EntityID, LPSCENE> scenes;
	EntityID current_scene;
	Game();
public:
	static Game * GetInstance();
	void virtual init(HINSTANCE hInstance, int nCmdShow);
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