#include "MenuScreen.h"
#include "../GameObjects/GameObject.h"
#include "../SpriteManagements/Sprites.h"
#include "../Animations/Animations.h"
#include "../Input/DirectInput.h"
#include "../AudioManager.h"

constexpr int  ID_TEX_MAINMENU = 1;

void MenuScreen::init()
{
	resourceManagement = ResourceManagement::GetInstance();
}

void MenuScreen::update(float dt)
{

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

void MenuScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_MAINMENU, L"Resources\\Screens\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMenu = resourceManagement->textures->Get(ID_TEX_MAINMENU);
	loadBackGround = new Sprite("Texture", 0, 0, 640, 480, texMenu);

	//AudioManager::getInstance()->loadAudio({
	//	{
	//		"intro_scene", L"Resources\\Sounds\\Musics\\intro_scene.wav" }
	//	});
	//AudioManager::getInstance()->playAudioLoop("intro_scene");

}

void MenuScreen::OnKeyDown(int keycode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", keycode);

	if(keycode == DIK_SPACE)
	{
		chooseScreenGamePlay(gamePlayScreen);
	}
}

MenuScreen::MenuScreen()
{
	DirectInput* directInput = DirectInput::getInstance();
	__hook(&DirectInput::OnKeyDown, directInput, &MenuScreen::OnKeyDown);
}

MenuScreen::~MenuScreen()
{
	DirectInput* directInput = DirectInput::getInstance();
	__unhook(&DirectInput::OnKeyDown, directInput, &MenuScreen::OnKeyDown);
}

