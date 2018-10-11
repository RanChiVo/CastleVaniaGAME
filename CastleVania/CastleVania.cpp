#include "CastleVania.h"

CastleVania* CastleVania::__instance = nullptr;


CastleVania::CastleVania()
{
	Game::Game();
}
void CastleVania::init(HINSTANCE hInstance, int nCmdShow)
{	
	Game::Init(hInstance, nCmdShow);
	KeyHandler * keyHandler;
	keyHandler = new KeyHandler();
	Game::InitKeyboard(keyHandler);
}

void CastleVania::loadResource()
{
	simon = new Simon();
	simon->loadResource();
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
