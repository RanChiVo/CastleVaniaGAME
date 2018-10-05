#pragma once
#include "../GameObjects/GameObject.h"

#define SIMON_MOVE_SPEED 0.1f
#define SIMON_JUMP_VEL 350
#define SIMON_JUMP_SPEED_X	1.0f
#define SIMON_JUMP_SPEED_Y	0.5f

#define SIMON_GRAVITY 0.02f
#define SIMON_ATTACK_TIME 600
#define SIMON_PROTECT_TIME 2000

#define SIMON_LEVEL_SMALL	0
#define SIMON_LEVEL_SUPER	1
#define SIMON_LEVEL_FIRE	2

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300


#define SIMON_ANI_IDLE_RIGHT	0
#define SIMON_ANI_IDLE_LEFT		1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3


class Simon: public GameObject
{
	int level;

public:
	Simon();

	void initialize();
	void loadResource();
	void Update(DWORD dt);
	void Render();

	int GetLevel() { return level; }

	void SetState(int state);
	~Simon();
};

	