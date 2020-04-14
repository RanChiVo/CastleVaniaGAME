#include "Scene.h"

Scene::Scene(EntityID id, std::string filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
}