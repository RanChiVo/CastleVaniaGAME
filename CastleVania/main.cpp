#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Game.h"
#include "CastleVania.h"
#include "ResourceManagement.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CastleVania *gameCastleVania = CastleVania::GetInstance();

	gameCastleVania->Init(hInstance, nCmdShow);

	gameCastleVania->loadResource();

	gameCastleVania->Run();

	delete gameCastleVania;

	return 0;
}