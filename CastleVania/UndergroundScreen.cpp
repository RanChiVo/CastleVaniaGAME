#include "UndergroundScreen.h"
#include "GameObjects/Simon.h"
#include "ObjectGridCreation.h"

UndergroundScreen::UndergroundScreen()
{
	path = "ReadSprite.txt";
	IdScreen = ID_ENTITY_MAP_UNDERGROUND;
}

void UndergroundScreen::loadResources()
{
	ScreenBase::loadResources();
	//ObjectGridCreation* Addproperty = new ObjectGridCreation("TiledMap\\BasementCaslte_map - Copy.tmx");
	//Addproperty->divideOnjectToGrid(&objects, 2, 4);
	grid = new Grid(2, 4);
	grid->loadObjects(&objects);
}

void UndergroundScreen::update(DWORD dt)
{
	ScreenBase::update(dt);

	updateViewport(dt);
}

void UndergroundScreen::updateViewport(DWORD dt)
{
	if (viewport->getState() == viewport->STATE_ACTION)
	{
		D3DXVECTOR2 pos_Simon = Simon::getInstance()->getPosition();
		int widthframeSimon = Simon::getInstance()->getWidth();
		D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};
		newPosViewport.x = Simon::getInstance()->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
		newPosViewport.x = min(resourceManagement->getTiledMap(IdScreen)->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
		newPosViewport.y = min(resourceManagement->getTiledMap(IdScreen)->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
		newPosViewport.x = max(0, newPosViewport.x);
		newPosViewport.y = max(0, newPosViewport.y);
		viewport->setX(float(newPosViewport.x));
		viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
	}
	else return;
}

UndergroundScreen::~UndergroundScreen()
{
}
