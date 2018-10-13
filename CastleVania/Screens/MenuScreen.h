#pragma once
#include "ScreenBase.h"
#include "../SpriteManagements/Sprite.h"
#include "../ResourceManagement.h"
#include "../Game.h"
#include "../Input/DirectInput.h"
#include "../GameObjects/GameObject.h"
#include "../SingleObjectManager.h"

class MenuScreen : public ScreenBase, public SingleObjectManager
{
private: 
	bool isRender = false;
	bool isplayGame = false;
	vector<GameObject> objects;

public:

	bool init();
	void update(float dt);
	void render();
	void handleInput();
	void loadResources();

	MenuScreen();
	~MenuScreen();
};

