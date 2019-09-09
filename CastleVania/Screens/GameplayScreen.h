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
#include "../GameObjects/Entrance.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Input/DirectInput.h"
#include "../Viewport.h"
#include "../Game.h"
#include "../MenuPoint.h"

class GameplayScreen: public ScreenBase
{
private:
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objectslv2;
	D3DXVECTOR2 posWall;
	EntityID id;
	Simon* simon;
	DirectInput* directInput;
	ResourceManagement* resourceManagement;
	RECT rect;
	DWORD timer_zombie = 0;
	DWORD TIME_ZOMBIE = 5000;
	MenuPoint* menu_point;
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

