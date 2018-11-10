#pragma once
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../Input/DirectInput.h"
#include "../TiledMap.h"

class ScreenBase
{
protected:
	//ViewPort * Viewport;
public:
	ScreenBase();
	//ViewPort * getViewPort() { return Viewport; }
	//void setViewPort(ViewPort* viewport) { viewport = Viewport; }

	void virtual init() = 0;
	void virtual update(float deltatime) = 0;
	void virtual loadResources() = 0;
	void virtual renderObject() = 0;

	virtual~ScreenBase();
};

