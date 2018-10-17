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

void GameplayScreen::handleInput()
{
	DWORD dwElements = directInput->getDiviceData();
	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = directInput->getKeyEvents(i).dwOfs;
		int KeyState = directInput->getKeyEvents(i).dwData;
		if ((KeyState & 0x80) > 0)
			simon->OnKeyDown(KeyCode);
		else
			simon->OnKeyUp(KeyCode);
	}
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
}
