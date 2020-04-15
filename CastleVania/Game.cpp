#include "Game.h"
#include "DebugOut/DebugOut.h"
#include "Utils.h"
#include "PlayScence.h"

constexpr unsigned int ScreenBase_width = 550;
constexpr unsigned int ScreenBase_height = 540;
constexpr int max_frame_rate = 120;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)
Game* Game::__instance = nullptr;

Game * Game::GetInstance()
{
	if (__instance == nullptr)
		__instance = new Game();
	return __instance;
}

Game::Game()
{
	direct3D = Direct3DManager::getInstance();
	directInput = DirectInput::getInstance();
}

void Game::init(HINSTANCE hInstance, int nCmdShow)
{
	WindowUtil* window = new WindowUtil(hInstance, nCmdShow, ScreenBase_width, ScreenBase_height);

	direct3D->init(window);

	HWND hWnd = direct3D->gethWnd();

	directInput->initKeyboard(hWnd);
}

void Game::update(DWORD dt)
{
	GetCurrentScene()->Update(dt);
}

void Game::Load(std::string gameFile)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(gameFile.c_str());

	if (!result)
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
		return;
	}

	auto sceneManagerNode = doc.child("sceneManager");
	current_scene = Utils::getInstance()->getStringToEntityID()[sceneManagerNode.child("startScene").attribute("id").as_string()];
	auto sceneListNode = sceneManagerNode.child("sceneList");
	for (auto sceneNode : sceneListNode.children("scene"))
	{
		std::string pathMap = sceneNode.attribute("mapPath").as_string();
		EntityID id = Utils::getInstance()->getStringToEntityID()[sceneNode.attribute("id").as_string()];
		LPSCENE scene = new PlayScene(id, pathMap);
		scenes[id] = scene;
	}

	SwitchScene(current_scene);
}

void Game::SwitchScene(EntityID scene_id)
{
	current_scene = scene_id;

	LPSCENE s = scenes[current_scene];
	s->Unload();

	Textures::GetInstance()->Clear();
	Sprites::GetInstance()->Clear();
	Animations::GetInstance()->Clear();

	s->Load();
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

		GetCurrentScene()->Render(Direct3DManager::getInstance()->getViewport());

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


