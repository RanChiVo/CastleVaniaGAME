#include "Game.h"
#include "DebugOut/DebugOut.h"
#include "AudioManager.h"

Game::Game()
{
	direct3D = Direct3DManager::getInstance();
	directInput = DirectInput::getInstance();
}

void Game::init(HINSTANCE hInstance, int nCmdShow)
{
	int extra_width = 15;
	int extra_height = 38;

	WindowUtil* window = new WindowUtil(hInstance, nCmdShow, ScreenBase_width + extra_width, ScreenBase_height + extra_height);

	direct3D->init(window);

	HWND hWnd = direct3D->gethWnd();

	AudioManager::getInstance()->initialize(hWnd);

	directInput->initKeyboard(hWnd);	
}

void Game::update(float dt)
{
}

void Game::renderObjects()
{
}

void Game::loadResource()
{
}

void Game::handleInput()
{
}

void Game::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = direct3D->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = direct3D->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = direct3D->GetSpriteHandler();

	if (direct3D->GetDirect3DDevice()->BeginScene())
	{
		// clearBackBuffer back buffer with a color
		direct3D->clearBackBuffer();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		renderObjects();

		spriteHandler->End();

		direct3D->GetDirect3DDevice()->EndScene();
	}
	// Display back buffer content to the ScreenBase
	direct3D->callPresent();
}

int Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / int(max_frame_rate);
	
	while (!done)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			directInput->ProcessKeyboard();

			update(dt);

			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}
	return 1;
}

Game::~Game()
{
	
}


