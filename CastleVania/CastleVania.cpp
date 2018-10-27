#include "CastleVania.h"
#include "ScreenManager.h"


CastleVania* CastleVania::__instance = nullptr;


CastleVania::CastleVania():Game()
{
	menuscreen = new MenuScreen();
	screenmanager = new ScreenManager();
	__hook(&MenuScreen::chooseScreenGamePlay, menuscreen, &CastleVania::playGame);
}
void CastleVania::Init(HINSTANCE hInstance, int nCmdShow)
{	
	Game:init(hInstance, nCmdShow);
	screenmanager->addScreen(new (MenuScreen));
}

void CastleVania::renderObjects()
{
	screenmanager->renderObject();
}

void CastleVania::loadResource()
{
	screenmanager->loadResources();
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

void CastleVania::playGame(ScreenBase * screen)
{
	screenmanager->changeScreen(new GameplayScreen());
}

CastleVania::~CastleVania()
{
	__unhook(&MenuScreen::chooseScreenGamePlay, menuscreen, &CastleVania::playGame);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    