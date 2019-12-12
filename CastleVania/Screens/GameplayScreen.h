#pragma once
#include "../GameObjects/Simon.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Viewport.h"
#include "../Game.h"


class GameplayScreen: public ScreenBase
{
private:
	EntityID mapId;
	bool checkSimonInSpawn = false;
	ResourceManagement* resourceManagement;
	EntityID idEnemy;
	RECT rect;
	DWORD timer_zombie = 0;
	DWORD TIME_ZOMBIE = 10000;
	int RandomEnemy = 1;
	Viewport* viewport;
	bool isActive = false;
	int time = 0;
public:
	GameplayScreen();
	void init() override;
	void loadResources() override;
	void update(DWORD dt) override;
	void renderObject(Viewport* viewport) override;
	void updateViewport(DWORD dt);
	void updateMap();
	void updateEnemy();
	void createZombie(Viewport* viewport);
	
	~GameplayScreen();
};

