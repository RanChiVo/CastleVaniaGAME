#include "Game.h"
#include "Debug/DebugOut.h"
#include "WindowUtil.h"
#include "Direct3DManager.h"

constexpr unsigned int screen_width = 640;
constexpr unsigned int screen_height = 480;
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)

void Game::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, nullptr
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, nullptr);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = keyboard_buffer_size; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	this->keyHandler = handler;
	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

Game::Game()
{
	direct3D = Direct3DManager::getInstance();
}

void Game::Init(HINSTANCE hInstance, int nCmdShow)
{
	WindowUtil* window = new WindowUtil(hInstance, nCmdShow, screen_width, screen_height);

	direct3D->init(window);

	hWnd = direct3D->gethWnd();
}

void Game::Update()
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

		simon->Render();

		spriteHandler->End();

		direct3D->GetDirect3DDevice()->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(nullptr, nullptr, nullptr, nullptr);
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

			ProcessKeyboard();

			simon->Update(dt);

			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int Game::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void Game::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE *)&keyStates);

	// Collect all buffered events
	DWORD dwElements = keyboard_buffer_size;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

Game::~Game()
{

}


