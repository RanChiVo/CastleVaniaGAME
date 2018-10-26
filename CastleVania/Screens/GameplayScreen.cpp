#include "GameplayScreen.h"


void GameplayScreen::init()
{
	
}

void GameplayScreen::update(float dt)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}

void GameplayScreen::renderObject()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void GameplayScreen::loadResources()
{
	simon->loadResource();

	objects.push_back(simon);
}

GameplayScreen::GameplayScreen()
{
	directInput = DirectInput::getInstance();

	simon = new Simon();
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
