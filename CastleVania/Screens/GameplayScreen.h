#pragma once
#include "../GameObjects/Simon.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Viewport.h"
#include "../Game.h"
#include "../MenuPoint.h"

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
	void update(DWORD dt) override;
	void updateViewport(DWORD dt);
	void renderObject() override;
	void createZombie(Viewport* viewport);
	void getInfoFromObjectInfo( ObjectInfo *info, LPGAMEOBJECT object);

	GameplayScreen();
	~GameplayScreen();
};

