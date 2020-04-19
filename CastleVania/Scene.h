#pragma once
#include "Viewport.h"
#include <string>
#include "EntityID.h"
#include <d3dx9.h>
#include "KeyEventHandler.h"

using namespace std;

class Scene
{
protected:
	int id;
	std::string sceneFilePath;
	KeyEventHandler * key_handler;
public:
	Scene(EntityID id, std::string filePath);
	KeyEventHandler * GetKeyEventHandler() { return key_handler; }

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render(Viewport* viewport) = 0;
};
typedef Scene * LPSCENE;

class ScenceKeyHandler : public KeyEventHandler
{
protected:
	Scene * scence;

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	ScenceKeyHandler(Scene *s) :KeyEventHandler() { scence = s; }
};