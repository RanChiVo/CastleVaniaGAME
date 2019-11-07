#pragma once
#include <stdio.h>  
#include "ScreenBase.h"
#include "../SpriteManagements/Sprite.h"
#include "../ResourceManagement.h"
#include "../Game.h"
#include "../GameObjects/GameObject.h"
#include "../Screens/GameplayScreen.h"


[event_source(native)]
class MenuScreen : public ScreenBase
{
private: 

	bool isRender = false;
	bool isplayGame = false;
	Sprite* loadBackGround;
	ResourceManagement* resourceManagement;
	GameplayScreen* gamePlayScreen;

public:

		void init() override;
		void update(DWORD dt) override;
		void renderObject() override;
		void loadResources() override;

		void OnKeyDown(int keycode);
		__event void chooseScreenGamePlay(ScreenBase* screen);

	MenuScreen();
	~MenuScreen();
};

