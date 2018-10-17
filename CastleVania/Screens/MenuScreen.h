#pragma once
#include "ScreenBase.h"
#include "../SpriteManagements/Sprite.h"
#include "../ResourceManagement.h"
#include "../Game.h"
#include "../GameObjects/GameObject.h"

class MenuScreen : public ScreenBase
{
private: 

	bool isRender = false;
	bool isplayGame = false;
	Sprite* loadBackGround;
	ResourceManagement* resourceManagement;

public:

		void init() override;
		void update(float dt) override;
		void renderObject() override;
		void handleInput() override;
		void loadResources() override;

	MenuScreen();
	~MenuScreen();
};

