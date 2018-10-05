#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Debug/DebugOut.h"
#include "Game.h"
#include "CastleVania.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CastleVania *gameCastleVania = CastleVania::GetInstance();
	
	gameCastleVania->init(hInstance, nCmdShow);

	gameCastleVania->loadResource();

	gameCastleVania->Run();

	return 0;
	
}