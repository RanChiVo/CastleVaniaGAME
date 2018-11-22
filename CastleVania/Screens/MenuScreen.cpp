#include "MenuScreen.h"
#include "../GameObjects/GameObject.h"
#include "../SpriteManagements/Sprites.h"
#include "../Animations/Animations.h"
#include "../Input/DirectInput.h"
#include "../AudioManager.h"
#include "../Direct3DManager.h"


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
	loadBackGround->Draw(D3DXVECTOR2(0, 0));

	RECT R;
	R.left = 180;
	R.top = 300;
	R.right = 2000;
	R.bottom = 2000;

	LPD3DXSPRITE spriteHandler = Direct3DManager::getInstance()->GetSpriteHandler();

	if (resourceManagement->getFont())
		resourceManagement->getFont()->DrawTextA(spriteHandler, "VO THI MOT", -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 0, 255));
}

void MenuScreen::loadResources()
{
	resourceManagement->loadFont(L"Resources\\Fonts\\prstart.ttf");
	auto font = resourceManagement->getFont();
	
	AudioManager::getInstance()->loadAudio({
		{
			"intro_scene", L"Resources\\Sounds\\Musics\\intro_scene.wav" }
		});
	AudioManager::getInstance()->playAudioLoop("intro_scene");
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
}

MenuScreen::~MenuScreen()
{
	DirectInput* directInput = DirectInput::getInstance();
}

