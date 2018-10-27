#include "CastleVania.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include "Screens/GameplayScreen.h"

CastleVania* CastleVania::__instance = nullptr;


CastleVania::CastleVania():Game()
{
	screenmanager = new ScreenManager();
	
}
void CastleVania::Init(HINSTANCE hInstance, int nCmdShow)
{	
	Game:init(hInstance, nCmdShow);
	screenmanager->addScreen(new GameplayScreen());
	screenmanager->init();
}

void CastleVania::renderObjects()
{
	screenmanager->renderObject();
}

void CastleVania::loadResource()
{
	screenmanager->loadResources();
}

void CastleVania::handleInput()
{
	screenmanager->handleInput();
}

void CastleVania::update(float dt)
{
	screenmanager->update(dt);
}

CastleVania * CastleVania::GetInstance()
{
	if (__instance == nullptr) __instance = new CastleVania();
	return __instance;
}

void CastleVania::run()
{
	Run();
}

CastleVania::~CastleVania()
{
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    