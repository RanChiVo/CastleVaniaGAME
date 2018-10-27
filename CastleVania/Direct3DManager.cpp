#include "Direct3DManager.h"


Direct3DManager* Direct3DManager::_instance = nullptr;

Direct3DManager::Direct3DManager()
{
}

void Direct3DManager::init(WindowUtil * windowGame)
{
	HWND hWnd = windowGame->CreateGameWindow();

	this->hWnd = hWnd;

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
		
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == nullptr)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");	
}

void Direct3DManager::clearBackBuffer()
{	
	this->d3ddv->ColorFill(backBuffer, nullptr, D3DCOLOR_XRGB(0, 0, 0));
}

void Direct3DManager::callPresent()
{//display the back buffer on the screen
	this->d3ddv->Present(0, 0, 0, 0);
}

HWND Direct3DManager::gethWnd()
{
	return this->hWnd;
}

Direct3DManager * Direct3DManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new Direct3DManager();
	return _instance;
}

Direct3DManager::~Direct3DManager()
{
	if (d3d != nullptr)
		d3d->Release();
	if (d3ddv != nullptr)
		d3ddv->Release();
	if (backBuffer != nullptr)
		backBuffer->Release();
}
