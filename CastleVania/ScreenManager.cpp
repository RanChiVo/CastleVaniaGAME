#include "ScreenManager.h"


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

void ScreenManager::update(float dt)
{
	if (!screens.empty())
		screens.back()->update(dt);
}

void ScreenManager::renderObject()
{
	if (!screens.empty())
		screens.back()->renderObject();
}

void ScreenManager::addScreen(ScreenBase* _screen)
{
	screens.push_back(_screen);
	screens.back()->init();
}

void ScreenManager::removeScreen()
{
	if (!screens.empty())
	{
		delete screens.back();
		screens.pop_back();
	}
}

void ScreenManager::changeScreen(ScreenBase * _screen)
{
	this->removeScreen();
	this->addScreen(_screen);
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
