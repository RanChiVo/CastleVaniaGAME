#include "CastleVania.h"
#include "ScreenManager.h"
#include "ResourceManagement.h"
#include "Direct3DManager.h"

CastleVania::CastleVania()
{
	screenmanager = new ScreenManager();
	viewport = Direct3DManager::getInstance()->getViewport();
}

void CastleVania::Init(HINSTANCE hInstance, int nCmdShow)
{	
	Game::init(hInstance, nCmdShow);
	screenmanager->addScreen(new GameplayScreen());
}

void CastleVania::render()	
{	
	screenmanager->renderObject(viewport);
}

void CastleVania::loadResource()
{
	screenmanager->loadResources();
}

void CastleVania::update(DWORD dt)
{
	screenmanager->update(dt);
}

void CastleVania::run()
{
	Game::Run();
}

CastleVania::~CastleVania()
{
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    