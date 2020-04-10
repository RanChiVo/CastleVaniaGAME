#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Viewport.h"
#include "TiledMap.h"
#include "MenuPoint.h"
#include "Grid.h"

class Scene
{
protected:
	int id;
	std::string sceneFilePath;
public:
	Scene(int id, std::string filePath);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};

