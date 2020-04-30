#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* gameCastleVania = Game::GetInstance();

	gameCastleVania->init(hInstance, nCmdShow);

	gameCastleVania->InitKeyboard();

	gameCastleVania->Load("Castlevania.xml");

	gameCastleVania->Run();

	return 0;
}