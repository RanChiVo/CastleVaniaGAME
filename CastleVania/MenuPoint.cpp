#include "MenuPoint.h"
#include "DarkBat.h"

MenuPoint::MenuPoint()
{
	startTime = GetTickCount();
	subWeapon = nullptr;
	idSubWeapon = EntityID::ID_ENTITY_NULL;
}

void MenuPoint::loadResource()
{
	Textures::GetInstance()->Add(ID_ENTITY_BBOX, L"Resources\\menu.png", D3DCOLOR_XRGB(255, 255, 255));
	menu = Sprites::GetInstance()->Get("menu");
	heart = Sprites::GetInstance()->Get("heartMenuPoint");
	HP = Sprites::GetInstance()->Get("HP1");
	enemy_HP1 = Sprites::GetInstance()->Get("enemy_HP1");
	lost_HP = Sprites::GetInstance()->Get("lost_HP1");
	place_item1 = Sprites::GetInstance()->Get("place_item1");
	spriteHandler = Direct3DManager::getInstance()->GetSpriteHandler();
	R = RECT{ 15, 20, 550, 528 };
	itemList[ID_ENTITY_DAGGER_WEAPON] = Sprites::GetInstance()->Get("dagger");
	itemList[ID_ENTITY_AXE_WEAPON] = Sprites::GetInstance()->Get("axe1");
	itemList[ID_ENTITY_FIRE_BOMP_WEAPON] = Sprites::GetInstance()->Get("fire_bomb");
	itemList[ID_ENTITY_STOP_WATCH] = Sprites::GetInstance()->Get("stop_watch1");
	itemList[ID_ENTITY_BOOMERANG_WEAPON] = Sprites::GetInstance()->Get("bomerang1");
}

void MenuPoint::update(DWORD dt)
{
	gameTime = 300 - (GetTickCount() - startTime) / 1000;
	
	if (Simon::getInstance()->getBaseInfo()->getIdSubWeapon()!= idSubWeapon)
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
		default:
			subWeapon = nullptr;
			break;
		}
	}

	scoreStringTemp = std::to_string(min(Simon::getInstance()->getBaseInfo()->getScore(), 999999));

	scoreString = scoreStringTemp;

	for (int i = 0; i < (6 - scoreStringTemp.length()); i++)
	{
		scoreString = "0" + scoreString;
	}
	
	heartScore = std::to_string(Simon::getInstance()->getBaseInfo()->getHeart());

	if (Simon::getInstance()->getBaseInfo()->getHeart() < 10)
	{
		heartScore = "0" + heartScore;
	}
	healthSimon = Simon::getInstance()->getBaseInfo()->getHealth();

	healthDarkBat = DarkBat::getBaseInfo().getHealth();
}

void MenuPoint::Draw(ID3DXFont* font)
{
	timeString = std::to_string(gameTime);
	menu->Draw(D3DXVECTOR2(0, 0), Flip::normal, 255);
	content = "SCORE-"+ scoreString + " TIME " + timeString + " STAGE 01\n";
	content += "PLAYER			                 -"+ heartScore +"\n";
	content += "ENEMY                 P-03\n";
	heart->Draw(D3DXVECTOR2(385.0f, 35.0f), Flip::normal, 255);

	for (int i = 0; i < 16; i++)
	{
		lost_HP->Draw(D3DXVECTOR2(125.0f + 10.0f * i, 37.0f), Flip::normal, 255);
		lost_HP->Draw(D3DXVECTOR2(125.0f + 10.0f * i, 55.0f), Flip::normal, 255);
	}

	for (int i = 0; i < healthDarkBat; i++)
	{
		enemy_HP1->Draw(D3DXVECTOR2(125.0f + 10.0f * i, 55.0f), Flip::normal, 255);
	}

	for (int i = 0; i < healthSimon; i++)
	{
		HP->Draw(D3DXVECTOR2(125.0f + 10.0f * i, 37.0f), Flip::normal, 255);
	}

	place_item1->Draw(D3DXVECTOR2(300.0f, 38.0f), Flip::normal, 255);

	if (subWeapon)
	{
		subWeapon->Draw(D3DXVECTOR2(318.0f, 45.0f), Flip::normal, 255);

	}
	if (font)
		font->DrawTextA(spriteHandler, content.c_str(), -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

MenuPoint::~MenuPoint()
{
}
