#include "OptionScene.h"
#include "Direct3DManager.h"
#include "SpriteManagements/Sprites.h"
#include "Game.h"

D3DXVECTOR2 POS_CONTINUTE = D3DXVECTOR2(180, 230);
D3DXVECTOR2 POS_END = D3DXVECTOR2(180, 262);

OptionScene::OptionScene(EntityID id, std::string filePath) :Scene(id, filePath)
{
	id = ID_ENTITY_OPTION_SCENE;
	key_handler = new OptionSceneKeyHandler(this);
	menuPoint = new MenuPoint();
}	

void OptionScene::Load()
{
	menuPoint->loadResource();

	ReadFile_FONTS(L"Resources\\Fonts\\prstart.ttf");

	heart = Sprites::GetInstance()->Get("heart1");

	R = RECT{ 180, 180, 550, 400 };

	content = "GAME OVER\n\n\n";
	content += "  CONTINUTE\n\n";
	content += "  END";

	positionHeart = POS_CONTINUTE;
}

void OptionScene::Unload()
{
}

void OptionScene::Update(DWORD dt)
{
	menuPoint->update(dt);
}

void OptionScene::Render(Viewport * viewport)
{
	menuPoint->Draw(font);

	if (font)
		font->DrawTextA(Direct3DManager::getInstance()->GetSpriteHandler() , content.c_str(), -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	heart->Draw(positionHeart, Flip::normal, 255);
}

void OptionScene::ReadFile_FONTS(LPTSTR path)
{
	LPDIRECT3DDEVICE9 gDevice = Direct3DManager::getInstance()->GetDirect3DDevice();

	AddFontResourceEx(path, FR_PRIVATE, NULL);

	HRESULT result = D3DXCreateFont(
		gDevice, 17, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);
}

void OptionScene::SetPosHeart(D3DXVECTOR2 pos)
{
	this->positionHeart = pos;
}

D3DXVECTOR2 OptionScene::GetPosHeart()
{
	return positionHeart;
}

OptionScene::~OptionScene()
{
}

void OptionSceneKeyHandler::KeyState(BYTE * states)
{
}

void OptionSceneKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
	case DIK_DOWN:
		if (dynamic_cast<OptionScene*>(Game::GetInstance()->GetCurrentScene())->GetPosHeart()== POS_CONTINUTE)
		{
			dynamic_cast<OptionScene*>(Game::GetInstance()->GetCurrentScene())->SetPosHeart(POS_END);
		}
		else dynamic_cast<OptionScene*>(Game::GetInstance()->GetCurrentScene())->SetPosHeart(POS_CONTINUTE);
		break;
	case DIK_RETURN:
		if (dynamic_cast<OptionScene*>(Game::GetInstance()->GetCurrentScene())->GetPosHeart() == POS_CONTINUTE)
		{
			Game::GetInstance()->SwitchScene(Game::GetInstance()->GetCurrentSceneIdSaved());
		}
		else
		{
			Game::GetInstance()->SwitchScene(ID_ENTITY_MAP_ENTRANCE);
		}
		break;
	}
}

void OptionSceneKeyHandler::OnKeyUp(int KeyCode)
{
}
