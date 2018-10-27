#include "MenuScreen.h"
#include "../GameObjects/GameObject.h"
#include "../SpriteManagements/Sprites.h"
#include "../Animations/Animations.h"
#include "../Input/DirectInput.h"

constexpr int  ID_TEX_MAINMENU = 1;

void MenuScreen::init()
{
	resourceManagement = ResourceManagement::GetInstance();
}

void MenuScreen::update(float dt)
{
	if (isplayGame)
	{

	}

	int waitingTime = 5000;
	DWORD startTime = GetTickCount();
	DWORD interval = 20;

	for (int timer = 0; timer < waitingTime; timer += interval)
	{
		while (GetTickCount() < (startTime + interval))
		{
		}
		DWORD startTime = GetTickCount();
	}

}

void MenuScreen::renderObject()
{
	loadBackGround->Draw(0, 0);
}

void MenuScreen::handleInput()
{
	DirectInput* directInput = DirectInput::getInstance();

	if (directInput->IsKeyDown(DIK_SPACE))
	{
		isplayGame = true;
	}
}

void MenuScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_MAINMENU, L"Resources\\Screens\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMenu = resourceManagement->textures->Get(ID_TEX_MAINMENU);
	loadBackGround = new Sprite(5000, 0, 0, 640, 480, texMenu);
}

MenuScreen::MenuScreen()
{

}

MenuScreen::~MenuScreen()
{
}
