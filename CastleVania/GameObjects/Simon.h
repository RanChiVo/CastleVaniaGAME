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

	int level = 1;

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
		SIMON_STATE_IDLE_UP_STAIR_LEFT,
		SIMON_STATE_IDLE_DOWN_STAIR_RIGHT,
	};

	int ani;
	int untouchable;
	DWORD untouchable_start;
	bool jumped = false;
	bool attacking = false;
	bool checkRewind = false;
	bool throwKatana = false;
	bool isRender = true;
	bool checkUp = true;
	Whip* whip;
	KatanaWeapon* katanaWeapon;

	std::vector<LPGAMEOBJECT> objectList;
	std::vector< LPGAMEOBJECT> objectFloor;
	std::vector<LPGAMEOBJECT> itemList;

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

	