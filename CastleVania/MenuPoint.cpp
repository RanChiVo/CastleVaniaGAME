#include "MenuPoint.h"
#include "DarkBat.h"
#include "Game.h"

MenuPoint::MenuPoint()
{
	startTime = GetTickCount();
	subWeapon = nullptr;
	idSubWeapon = EntityID::ID_ENTITY_NULL;
}

void MenuPoint::loadResource()
{
	Textures::GetInstance()->Add(ID_ENTITY_MENU, L"Resources\\MenuPoint\\menu.png", D3DCOLOR_XRGB(255, 255, 255));
	menu = Sprites::GetInstance()->Get("menu");
	HP = Sprites::GetInstance()->Get("HP1");
	enemy_HP1 = Sprites::GetInstance()->Get("enemy_HP1");
	spriteHandler = Direct3DManager::getInstance()->GetSpriteHandler();
	R = RECT{ 5, 20, 550, 528 };
	itemList[ID_ENTITY_DAGGER_WEAPON] = Sprites::GetInstance()->Get("dagger");
	itemList[ID_ENTITY_AXE_WEAPON] = Sprites::GetInstance()->Get("axe1");
	itemList[ID_ENTITY_FIRE_BOMP_WEAPON] = Sprites::GetInstance()->Get("fire_bomb");
	itemList[ID_ENTITY_STOP_WATCH] = Sprites::GetInstance()->Get("stop_watch1");
	itemList[ID_ENTITY_BOOMERANG_WEAPON] = Sprites::GetInstance()->Get("bomerang1");
	itemList[ID_ENTITY_DOUBLE_SHOOT] = Sprites::GetInstance()->Get("double_shoot1");
}

void MenuPoint::update(DWORD dt)
{
	stage = Game::GetInstance()->GetCurrentSceneId();

	stageString = std::to_string(stage);

	if (Simon::getInstance()->GetState() == Simon::SIMON_STATE_WIN)
	{
		gameTime -=1;

		if (gameTime <= 0)
		{
			Simon::getInstance()->getBaseInfo()->setHealth(min(16, Simon::getInstance()->getBaseInfo()->getHealth() + 1));
			Simon::getInstance()->getBaseInfo()->setHeart(Simon::getInstance()->getBaseInfo()->getHeart() - 0.5);
			if (scoreFinal == 0)
			{
				scoreFinal = Simon::getInstance()->getBaseInfo()->getHeart();
			}

			if (heartScore > 0)
			{
				Simon::getInstance()->getBaseInfo()->setHeart(max(0, Simon::getInstance()->getBaseInfo()->getHeart() - 1));
				Simon::getInstance()->getBaseInfo()->setScore(max(0, Simon::getInstance()->getBaseInfo()->getScore() + 1));
			}
			else if (heartScore == 0 && scoreFinal>0)
			{
				Simon::getInstance()->getBaseInfo()->setScore(Simon::getInstance()->getBaseInfo()->getScore()+ scoreFinal);
				scoreFinal = 0;
			}
		}
	}
	else
	{
		gameTime = 150 - (GetTickCount() - startTime) / 1000;
	}

	heartScore = Simon::getInstance()->getBaseInfo()->getHeart();

	score = min(Simon::getInstance()->getBaseInfo()->getScore(), 999999);

	if (gameTime < 0)
	{
		gameTime = 0;
	}

	//game time
	timeStringTemp = std::to_string(gameTime);

	timeString = timeStringTemp;

	for (int i = 0; i < (4 - timeStringTemp.length()); i++)
	{
		timeString = "0" + timeString;
	}

	//heart score
	heartScoreString = std::to_string(heartScore);

	if (heartScore < 10)
	{
		heartScoreString = "0" + heartScoreString;
	}

	//score
	scoreStringTemp = std::to_string(score);

	scoreString = scoreStringTemp;

	for (int i = 0; i < (5 - scoreStringTemp.length()); i++)
	{
		scoreString = "0" + scoreString;
	}

	//Lives

	livesString = std::to_string(Simon::getInstance()->getBaseInfo()->GetLives());

	if (Simon::getInstance()->getBaseInfo()->getIdSubWeapon() != idSubWeapon)
	{
		switch (Simon::getInstance()->getBaseInfo()->getIdSubWeapon())
		{
		case ID_ENTITY_DAGGER_WEAPON:
			subWeapon = itemList[ID_ENTITY_DAGGER_WEAPON];
			break;
		case ID_ENTITY_AXE_WEAPON:
			subWeapon = itemList[ID_ENTITY_AXE_WEAPON];
			break;
		case ID_ENTITY_FIRE_BOMP_WEAPON:
			subWeapon = itemList[ID_ENTITY_FIRE_BOMP_WEAPON];
			break;
		case ID_ENTITY_STOP_WATCH:
			subWeapon = itemList[ID_ENTITY_STOP_WATCH];
			break;
		case ID_ENTITY_BOOMERANG_WEAPON:
			subWeapon = itemList[ID_ENTITY_BOOMERANG_WEAPON];
			break;
		case ID_ENTITY_NULL:
			subWeapon = nullptr;
			break;
		}
	}

	healthSimon = Simon::getInstance()->getBaseInfo()->getHealth();
	if (DarkBat::IsActive())
	{
		healthDarkBat = DarkBat::getBaseInfo().getHealth();
	}
	else healthDarkBat = 16;

	subItem = itemList[Simon::getInstance()->getBaseInfo()->GetIdSubItem()];
}

void MenuPoint::Draw(ID3DXFont* font)
{
	menu->Draw(D3DXVECTOR2(0, 0), Flip::normal, 255);
	content = "      " + scoreString + "        " + timeString + "         "+ stageString +  "\n";
	content += "                           " + heartScoreString + "\n";
	content += "                            " + livesString + "\n";
	for (int i = 0; i < healthDarkBat; i++)
	{
		enemy_HP1->Draw(D3DXVECTOR2(125.0f + 10.0f * i, 55.0f), Flip::normal, 255);
	}

	for (int i = 0; i < healthSimon; i++)
	{
		HP->Draw(D3DXVECTOR2(125.0f + 10.0f * i, 37.0f), Flip::normal, 255);
	}

	if (subWeapon && Simon::getInstance()->getBaseInfo()->getIdSubWeapon()!= ID_ENTITY_NULL)
	{
		subWeapon->Draw(D3DXVECTOR2(318.0f, 45.0f), Flip::normal, 255);
	}

	if (subItem && Simon::getInstance()->getBaseInfo()->GetIdSubItem() != ID_ENTITY_NULL)
	{
		subItem->Draw(D3DXVECTOR2(455.0f, 38.0f), Flip::normal, 255);
	}

	if (font)
		font->DrawTextA(spriteHandler, content.c_str(), -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

MenuPoint::~MenuPoint()
{
}
