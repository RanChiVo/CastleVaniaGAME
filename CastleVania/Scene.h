#pragma once
#include "Viewport.h"
#include <string>
#include "EntityID.h"

using namespace std;


class Scene
{
protected:
	int id;
	std::string sceneFilePath;
public:
	Scene(EntityID id, std::string filePath);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render(Viewport* viewport) = 0;
};
typedef Scene * LPSCENE;

