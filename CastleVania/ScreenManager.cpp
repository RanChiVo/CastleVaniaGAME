#include "ScreenManager.h"
#include "../CastleVania/Screens/GameplayScreen.h"
#include "../CastleVania/EntranceScreen.h"
#include "UndergroundScreen.h"
#include "../CastleVania/GameObjects/Simon.h"

ScreenManager::~ScreenManager()
{
}

ScreenManager::ScreenManager()
{
}

bool ScreenManager::init()
{
	if (!screens.empty())
		screens.back()->init();

	return true;
}

void ScreenManager::loadResources()
{
	if (!screens.empty())
		screens.back()->loadResources();
}

void ScreenManager::update(DWORD dt)
{
	if (!screens.empty())
		screens.back()->update(dt);

	if (currentScreenID!= Simon::getInstance()->GetLevel())
	{
		changeScreen(Simon::getInstance()->GetLevel());
	}
}

void ScreenManager::renderObject(Viewport* viewport)
{
	if (!screens.empty())
		screens.back()->renderObject(viewport);
}

void ScreenManager::addScreen(ScreenBase* _screen)
{
	screens.push_back(_screen);
	screens.back()->init();
	currentScreenID = _screen->getIDScreen();
}

void ScreenManager::removeScreen()
{
	if (!screens.empty())
	{
		delete screens.back();
		screens.pop_back();
	}
}

void ScreenManager::changeScreen(int level)
{
	this->removeScreen();
	switch (level)
	{
	case 1:
		screen = new EntranceScreen();
		screen->loadResources();
		break;
	case 2:
		screen = new GameplayScreen();
		screen->loadResources();
		break;
	case 3:
		screen = new UndergroundScreen();
		screen->loadResources();
		break;
	}
	this->addScreen(screen);
	currentScreenID = screen->getIDScreen();
}

void ScreenManager::clearScreen()
{
	while (!screens.empty())
	{
		delete screens.back();
		screens.pop_back();
	}
}

ScreenBase * ScreenManager::getScene()
{
	if (!screens.empty())
		return screens.back();

	return nullptr;
}
