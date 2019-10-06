	#pragma once
#include "../GameObjects/GameObject.h"
#include "../ResourceManagement.h"
#include "../Input/DirectInput.h"
#include "../Animations/Animation.h"
#include "../GameObjects/Whip.h"
#include "../GameObjects/Katana.h"
#include "../KatanaWeapon.h"

class Simon: public GameObject
{
private: 
	DWORD comeEntranceStart = 0;
	enum State
	{
		SIMON_STATE_IDLE,
		SIMON_STATE_WALKING_RIGHT,
		SIMON_STATE_WALKING_LEFT,
		SIMON_STATE_JUMPING,
		SIMON_STATE_JUMPED,
		SIMON_STATE_JUMPTOUCHGROUND,
		SIMON_STATE_SITDOWN,
		SIMON_STATE_ATTACK_STAND,
		SIMON_STATE_ATTACK_SITDOWN,
		SIMON_STATE_ATTACK_JUMP,
		SIMON_STATE_DIE,
		SIMON_STATE_CHANGECOLOR,
		SIMON_STATE_CHANGECOLOR1,
		SIMON_STATE_GO_UP_STAIR_RIGHT,
		SIMON_STATE_GO_UP_STAIR_LEFT,
		SIMON_STATE_GO_DOWN_STAIR_RIGHT,
		SIMON_STATE_GO_DOWN_STAIR_LEFT,
		SIMON_STATE_IDLE_ON_STAIR,
		SIMON_STATE_ATTACK_UP_ON_STAIR_RIGHT,
		SIMON_STATE_ATTACK_UP_ON_STAIR_LEFT,
		SIMON_STATE_ATTACK_DOWN_ON_STAIR_RIGHT,
		SIMON_STATE_ATTACK_DOWN_ON_STAIR_LEFT,
		SIMON_STATE_HURT,
	};

	int ani;
	int untouchable;
	DWORD untouchable_start;
	bool isjumping = false;
	bool attacking = false;
	bool checkRewind = false;
	bool touchRect = false;
	bool isOnStair = false;
	float positition_stair;
	int new_y = 0;

	std::string stair_direction;
	Whip* whip;
	int levelWhip;
	int heartGift = 0;
	KatanaWeapon* katanaWeapon;

	std::vector<LPGAMEOBJECT> objectCollision;
	std::vector< LPGAMEOBJECT> objectItem;
	std::vector<LPGAMEOBJECT> enemyList;

	std::vector<LPGAMEOBJECT> itemList;
	std::vector<LPGAMEOBJECT> HPList;

public:
	Simon();
	int WHIP_STATE;

	void loadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	bool isOnGround();
	int GetLevel() { return level; }
	void handleState();
	void Reset(int currentAnimation);
	int IsAttacking();
	void handleCollisionStair();

	RECT getBoundingboxWhip();
	void RemoveWhip();
	void OnKeyStateChange(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	int getWidthWorld();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetState(int state);
	~Simon();
};

	