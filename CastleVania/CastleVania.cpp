#include "CastleVania.h"
#include "ScreenManager.h"
#include "ResourceManagement.h"

CastleVania::CastleVania()
{
	menuscreen = new MenuScreen();
	screenmanager = new ScreenManager();
}

void CastleVania::Init(HINSTANCE hInstance, int nCmdShow)
{	
	Game:init(hInstance, nCmdShow);
	screenmanager->addScreen(new GameplayScreen());
}

void CastleVania::renderObjects()	
{
	screenmanager->renderObject();
}

void CastleVania::loadResource()
{
	ResourceManagement::GetInstance()->loadResource();

	screenmanager->loadResources();
}

void CastleVania::update(float dt)
{
	screenmanager->update(dt);
}

void CastleVania::run()
{
	Run();
}

CastleVania::~CastleVania()
{
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    