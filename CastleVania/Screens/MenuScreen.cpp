#include "MenuScreen.h"
#include "../GameObjects/GameObject.h"
#include "../SpriteManagements/Sprites.h"
#include "../Animations/Animations.h"

constexpr int  ID_TEX_MAINMENU = 1;

bool MenuScreen::init()
{
	return false;
}

void MenuScreen::update(float dt)
{
	
}

void MenuScreen::render()
{
		
}

void MenuScreen::handleInput()
{
	/*if (directInput->IsKeyDown() == (1)
	{
		isplayGame = true;
	}*/
}

void MenuScreen::loadResources()
{

	resourceManagement->loadTexture(ID_TEX_MAINMENU, L"Resources\\Screens\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));

	resourceManagement->loadSprites(5000, 685, 0, 719, 48, ID_TEX_MAINMENU);

	


}

MenuScreen::MenuScreen()
{

}

MenuScreen::~MenuScreen()
{
}
