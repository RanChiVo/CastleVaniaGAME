#include "Game.h"
#include "Debug/DebugOut.h"


constexpr unsigned int ScreenBase_width = 640;
constexpr unsigned int ScreenBase_height = 480;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)

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

	hWnd = direct3D->gethWnd();

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

void Game::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom)
{
	D3DXVECTOR3 p(x, y, 0);	
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	direct3D->GetSpriteHandler()->Draw(texture, &r, nullptr, &p, D3DCOLOR_XRGB(255, 255, 255));
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
	constexpr int max_frame_rate = 90;
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

			handleInput();

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


