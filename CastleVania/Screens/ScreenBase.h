#pragma once
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../Input/DirectInput.h"
#include "../Viewport.h"
#include "../TiledMap.h"
#include "../MenuPoint.h"

class ScreenBase
{
protected:
	EntityID IdScreen;
	vector<LPGAMEOBJECT> objects;
	MenuPoint* menu_point;
	ResourceManagement* resourceManagement;
	Viewport* viewport;
	std::string path;
public:
	ScreenBase();
	void virtual init();
	void virtual update(DWORD deltatime);
	void virtual loadResources();
	void virtual renderObject(Viewport* viewport);
	void virtual getInfoFromObjectInfo(ObjectInfo::builder*, LPGAMEOBJECT object);
	EntityID getIDScreen() { return IdScreen; }
	virtual~ScreenBase();
};

