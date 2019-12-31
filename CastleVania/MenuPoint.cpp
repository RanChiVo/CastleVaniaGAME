#include "MenuPoint.h"
#include "../CastleVania/EntityID.h"


MenuPoint::MenuPoint()
{
	startTime = GetTickCount();
	resourceManagement = ResourceManagement::GetInstance();
	subWeapon = nullptr;
}

void MenuPoint::loadResource()
{
	Textures::GetInstance()->Add(ID_ENTITY_BBOX, L"Resources\\menu.png", D3DCOLOR_XRGB(255, 255, 255));
	menu = resourceManagement->getSprite(ID_ENTITY_MENU)->Get("menu");
	heart = resourceManagement->getSprite(ID_ENTITY_HEART)->Get("heartMenuPoint");
	HP = resourceManagement->getSprite(ID_ENTITY_HP)->Get("HP1");
	enemy_HP1 = resourceManagement->getSprite(ID_ENTITY_HP_ENEMY)->Get("enemy_HP1");
	lost_HP = resourceManagement->getSprite(ID_ENTITY_LOST_HP)->Get("lost_HP1");
	place_item1 = resourceManagement->getSprite(ID_ENTITY_PLACE)->Get("place_item1");
	resourceManagement->loadFont(L"Resources\\Fonts\\prstart.ttf");
	spriteHandler = Direct3DManager::getInstance()->GetSpriteHandler();
	R = RECT{ 15, 20, 550, 528 };
	font = resourceManagement->getFont();
}

void MenuPoint::update()
{
	gameTime = 300 - (GetTickCount() - startTime) / 1000;
	
	switch (Simon::getInstance()->getBaseInfo()->getIdSubWeapon())
	{
	case ID_ENTITY_DAGGER_WEAPON:
		subWeapon = resourceManagement->getSprite(ID_ENTITY_DAGGER)->Get("dagger");
		break;
	case ID_ENTITY_AXE_WEAPON:
		subWeapon = resourceManagement->getSprite(ID_ENTITY_AXE)->Get("axe1");
		break;
	case ID_ENTITY_FIRE_BOMP_WEAPON:
		subWeapon = resourceManagement->getSprite(ID_ENTITY_FIRE_BOMB)->Get("fire_bomb");
		break;
	case ID_ENTITY_STOP_WATCH:
		subWeapon = resourceManagement->getSprite(ID_ENTITY_STOP_WATCH)->Get("stop_watch1");
		break;
	default:
		subWeapon = nullptr;
		break;
	} 

	score = std::to_string(Simon::getInstance()->getBaseInfo()->getHeart());
	if (Simon::getInstance()->getBaseInfo()->getHeart() < 10)
	{
		score = "0" + score;
	}

	healthSimon = Simon::getInstance()->getBaseInfo()->getHealth();
}

void MenuPoint::Draw()
{
	timeString = std::to_string(gameTime);
	//menu->Draw(D3DXVECTOR2(0, 0), Flip::normal, 255);
	content = "SCORE_000000 TIME " + timeString + " STAGE 01\n";
	content += "PLAYER			                     "+ score +"\n";
	content += "ENEMY                    P-03\n";
	heart->Draw(D3DXVECTOR2(435.0f, 35.0f), Flip::normal, 255);

	for (int i = 0; i < 16; i++)
	{
		lost_HP->Draw(D3DXVECTOR2(125.0f + 12.0f * i, 39.0f), Flip::normal, 255);
		enemy_HP1->Draw(D3DXVECTOR2(125.0f + 12.0f * i, 59.0f), Flip::normal, 255);
	}

	for (int i = 0; i < healthSimon; i++)
	{
		HP->Draw(D3DXVECTOR2(125.0f + 12.0f * i, 39.0f), Flip::normal, 255);
	}

	place_item1->Draw(D3DXVECTOR2(360.0f, 38.0f), Flip::normal, 255);
	if (subWeapon)
	{
		subWeapon->Draw(D3DXVECTOR2(378.0f, 45.0f), Flip::normal, 255);

	}
	if (font)
		font->DrawTextA(spriteHandler, content.c_str(), -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

MenuPoint::~MenuPoint()
{
}
