#include "CastleVania.h"


CastleVania* CastleVania::__instance = NULL;

CastleVania::CastleVania()
{

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
	Sprites *sprites = Sprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	sprites->loadResource();
	animations->loadResource();
	simon = new Simon();
}

CastleVania * CastleVania::GetInstance()
{
	if (__instance == NULL) __instance = new CastleVania();
	return __instance;
}

void CastleVania::run()
{
	Run();
}

CastleVania::~CastleVania()
{
}
