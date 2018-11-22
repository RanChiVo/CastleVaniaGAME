#pragma once
#include "../GameObjects/Simon.h"
#include "../GameObjects/Whip.h"
#include "../GameObjects/BurnBarrel.h"
#include "../GameObjects/Heart.h"
#include "../GameObjects/WeaponReward.h"
#include "../GameObjects/Katana.h"
#include "../GameObjects/MiraculousBag.h"
#include "../GameObjects/Floor.h"
#include "../Brick.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Input/DirectInput.h"
#include "../Viewport.h"
#include "../Game.h"

class GameplayScreen: public ScreenBase
{
private:
	vector<LPGAMEOBJECT> objects;
	vector< LPGAMEOBJECT> staticObjects;
	vector<LPGAMEOBJECT> movecoObjects;
	Simon* simon;

	DirectInput* directInput;
	TiledMap * tile_map;
	ResourceManagement* resourceManagement;
	RECT rect;

public:

	void init() override;
	void loadResources() override;
	void update(float dt) override;
	void updateViewport(float dt);
	void renderObject() override;

	GameplayScreen();
	~GameplayScreen();
};

