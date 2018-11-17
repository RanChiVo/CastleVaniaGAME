#pragma once
#include "../GameObjects/Simon.h"
#include "../GameObjects/Whip.h"
#include "../GameObjects/BurnBarrel.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Input/DirectInput.h"
#include "../Viewport.h"
#include "../Game.h"

class GameplayScreen: public ScreenBase
{
private:
	vector<GameObject*> objects;
	vector<LPGAMEOBJECT> coObjects;
	Simon* simon;
	BurnBarrel* burnbarrel;
	Whip* whip;
	DirectInput* directInput;
	TiledMap * tile_map;
	ResourceManagement* resourceManagement;
	RECT rect;

public:

	void init() override;
	void update(float dt) override;
	void updateViewport(float dt);
	void renderObject() override;
	void loadResources() override;

	GameplayScreen();
	~GameplayScreen();
};

