#pragma once
#include "../GameObjects/Simon.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Viewport.h"
#include "../Game.h"


class GameplayScreen: public ScreenBase
{
private:
	bool checkSimonInSpawn = false;
	EntityID idEnemy;
	RECT rect;
	DWORD timer_zombie = 0;
	DWORD TIME_ZOMBIE = 10000;
	int RandomEnemy = 1;
	bool isActive = false;
	int time = 0;
	float widthGameWorld = 0;
	float heightGameWorld = 0;
	float startXDefault = 0;
public:
	GameplayScreen();
	void update(DWORD dt) ;
	void updateViewport(DWORD dt);
	void updateEnemy();
	void createZombie(Viewport* viewport);
	
	~GameplayScreen();
};

