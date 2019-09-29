#include "MenuPoint.h"
#include "../CastleVania/EntityID.h"


MenuPoint::MenuPoint()
{
	startTime = GetTickCount();
}

void MenuPoint::update()
{
	int gameTime = 300 - (GetTickCount() - startTime) / 1000;

	timeString = std::to_string(gameTime);

	resourceManagement = ResourceManagement::GetInstance();

	content = "SCORE_000000 TIME " + timeString + " STAGE 01\n";
	content += "PLAYER				                    -62\n";
	content += "ENEMY                    P-03\n";
}

void MenuPoint::Draw()
{
	resourceManagement->getSprite(ID_TEX_HEART)->Get("heart1")->Draw(D3DXVECTOR2(433, 35), Flip::normal);

	for (int i = 0; i < 16; i++)
	{
		resourceManagement->getSprite(ID_TEX_HP)->Get("HP1")->Draw(D3DXVECTOR2(125 + 12*i, 40), Flip::normal);
		resourceManagement->getSprite(ID_TEX_HP_ENEMY)->Get("enemy_HP1")->Draw(D3DXVECTOR2(125 + 12*i, 60), Flip::normal);
	}
	resourceManagement->getSprite(ID_TEX_PLACE)->Get("place_item1")->Draw(D3DXVECTOR2(330, 38), Flip::normal);

	resourceManagement->loadFont(L"Resources\\Fonts\\prstart.ttf");
	auto font = resourceManagement->getFont();

	LPD3DXSPRITE spriteHandler = Direct3DManager::getInstance()->GetSpriteHandler();
	RECT R = RECT{ 15, 20, 550, 528 };

	if (resourceManagement->getFont())
		resourceManagement->getFont()->DrawTextA(spriteHandler, content.c_str(), -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

MenuPoint::~MenuPoint()
{
}
