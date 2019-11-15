	#pragma once
#include "../GameObjects/GameObject.h"
#include "../Input/DirectInput.h"
#include "../Animations/Animation.h"
#include "../GameObjects/Whip.h"
#include "../DaggerWeapon.h"
#include "../CombatWeapon.h"
#include "../BaseInfo.h"
#include "../ObjectStair.h"

class Simon: public GameObject
{
private: 
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
		SIMON_STATE_ATTACK_STAND_SUBWEAPON,
		SIMON_STATE_ATTACK_SITDOWN,
		SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON,
		SIMON_STATE_ATTACK_JUMP,
		SIMON_STATE_ATTACK_JUMP_SUBWEAPON,
		SIMON_STATE_DIE,
		SIMON_STATE_CHANGECOLOR,
		SIMON_STATE_CHANGECOLOR1,
		SIMON_STATE_GO_UP_STAIR,
		SIMON_STATE_GO_DOWN_STAIR,
		SIMON_STATE_IDLE_UP_STAIR,
		SIMON_STATE_IDLE_DOWN_STAIR,
		SIMON_STATE_ATTACK_ON_STAIR,
		SIMON_STATE_HURT,
	};

	int ani;
	int untouchable;
	DWORD untouchable_start;
	DWORD comeEntranceStart = 0;
	bool enableSubWeapon = false;
	bool isjumping = false;
	bool attacking = false;
	bool checkRewind = false;
	bool touchRect = false;
	bool isOnStair = false;
	int directionStair;
	float positition_stair;
	ObjectStair* originalStair = nullptr;
	ObjectStair* reverseStair = nullptr;
	float new_y = 0;

	std::string stair_direction;
	Whip* whip;
	int levelWhip;
	int WHIP_STATE;
	int startThrowWeapon = 0;
	BaseInfo* baseInfo;
	std::vector<LPCOMBATWEAPON> subWeapon;
	std::vector<LPGAMEOBJECT> objectCollision;

public:
	Simon();
	virtual void loadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	bool isOnGround();
	int GetLevel() { return level; }
	void SetState(int state);
	void Reset(int currentAnimation);
	void handleState();
	void updateCollisionStair();
	void handleCollisionObjectGame(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void handleAfterCollision(vector<LPGAMEOBJECT> *coObjects, int id ,int i, vector<LPCOLLISIONEVENT> *coEvents);
	void handleCollisionIntersectedObject(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	void RemoveWhip();
	void SetupAtacking();
	void SetupSubWeapon(vector<LPGAMEOBJECT> *coObjects);
	void RenderWeapon(LPANIMATION animation, Viewport* viewport);
	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	void OnKeyStateChange(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	~Simon();
};

	