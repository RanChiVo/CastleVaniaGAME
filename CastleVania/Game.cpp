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

		direct3D->drawBoundingBox(300, 100, 100, 100, D3DCOLOR_XRGB(255, 255, 0), d3ddv);

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

void Game::SweptAABB(
	float ml,			// move left 
	float mt,			// move top
	float mr,			// move right 
	float mb,			// move bottom
	float dx,			// 
	float dy,			// 
	float sl,			// static left
	float st,
	float sr,
	float sb,
	float &t,
	float &nx,
	float &ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//
	//Tao hinh hinh chu nhat giua vao vi tri ban dau va vi tri ke tiep
	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return; // neu nam ngoai thi khong co va cham


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	} 
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

Game::~Game()
{
	
}


