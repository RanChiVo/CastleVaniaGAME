#pragma once
#include "../GameObjects/Simon.h"
#include "../GameObjects/Whip.h"
#include "../GameObjects/BurnBarrel.h"
#include "../GameObjects/Heart.h"
#include "../GameObjects/WeaponReward.h"
#include "../GameObjects/Dagger.h"
#include "../GameObjects/MiraculousBag.h"
#include "../GameObjects/Floor.h"
#include "../Brick.h"
#include "../GameObjects/Entrance.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Viewport.h"
#include "../Game.h"
#include "../MenuPoint.h"
#include "../CastleWall.h"

class GameplayScreen: public ScreenBase
{
private:
	vector<LPGAMEOBJECT> objects;
	EntityID mapId;
	Simon* simon;
	ResourceManagement* resourceManagement;
	RECT rect;
	DWORD timer_zombie = 0;
	DWORD TIME_ZOMBIE = 25000;
	MenuPoint* menu_point;
	bool moveMap = false;
	bool isActive = false;
	int time = 0;

public:

	void init() override;
	void loadResources() override;
	void update(float dt) override;
	void updateViewport(float dt);
	void renderObject() override;
	void createZombie(Viewport* viewport);
	void getInfoFromObjectInfo( ObjectInfo *info, LPGAMEOBJECT object);

	GameplayScreen();
	~GameplayScreen();
};

