#pragma once
#include "../GameObjects/GameObject.h"
#include "../ResourceManagement.h"
#include "../Input/DirectInput.h"

constexpr float SIMON_MOVE_SPEED = 0.1f;
constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.5f;

constexpr float SIMON_GRAVITY = 0.02f;
constexpr int SIMON_ATTACK_TIME = 600;
constexpr int SIMON_PROTECT_TIME = 2000;

constexpr int SIMON_LEVEL_SMALL = 0;
constexpr int SIMON_LEVEL_SUPER = 1;
constexpr int SIMON_LEVEL_FIRE = 2;

constexpr int SIMON_STATE_IDLE = 0;
constexpr int SIMON_STATE_WALKING_RIGHT = 100;
constexpr int SIMON_STATE_WALKING_LEFT = 200;
constexpr int SIMON_STATE_JUMPING_RIGHT = 300;
constexpr int SIMON_STATE_JUMPING_LEFT = 400;
constexpr int SIMON_STATE_SITDOWN_RIGHT = 500;
constexpr int SIMON_STATE_SITDOWN_LEFT = 600;

constexpr int SIMON_ANI_IDLE_RIGHT = 0;
constexpr int SIMON_ANI_IDLE_LEFT = 1;
constexpr int SIMON_ANI_WALKING_RIGHT = 2;
constexpr int SIMON_ANI_WALKING_LEFT = 3;

constexpr int SIMON_ANI_JUMPING_RIGHT = 4;
constexpr int SIMON_ANI_JUMPING_LEFT = 5;

constexpr int SIMON_ANI_SITDOWN_RIGHT = 6;
constexpr int SIMON_ANI_SITDOWN_LEFT = 7;

constexpr int SIMON_ANI_FACINGBACKWARD = 8;

class Simon: public GameObject
{
private: 

	int level;
	int isSitdown = 0;
	
public:
	Simon();

	void loadResource();
	void Update(DWORD dt);
	void Render();
	int GetLevel() { return level; }

	void OnKeyStateChange(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	
	

	void SetState(int state);
	~Simon();
};

	