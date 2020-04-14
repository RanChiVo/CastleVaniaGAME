#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*CastleVania *gameCastleVania = new CastleVania();

	gameCastleVania->Init(hInstance, nCmdShow);

	gameCastleVania->loadResource();

	gameCastleVania->Run();

	delete gameCastleVania;*/



	Game* gameCastleVania = Game::GetInstance();

	gameCastleVania->init(hInstance, nCmdShow);

	gameCastleVania->Load("Castlevania.xml");

	gameCastleVania->Run();


	return 0;
}