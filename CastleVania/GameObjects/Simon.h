#pragma once
#include "../GameObjects/GameObject.h"
#include "../ResourceManagement.h"
#include "../Input/DirectInput.h"
#include "../Animations/Animation.h"
#include "../GameObjects/Whip.h"
#include "../GameObjects/Katana.h"
#include "../KatanaWeapon.h"

constexpr float SIMON_MOVE_SPEED = 0.1f;
constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.5f;

constexpr float SIMON_GRAVITY = 0.001f;
constexpr int SIMON_ATTACK_TIME = 600;
constexpr int SIMON_PROTECT_TIME = 2000;

constexpr int SIMON_ANI_IDLE = 0;
constexpr int SIMON_ANI_WALKING = 1;

constexpr int SIMON_ANI_JUMPING = 2;

constexpr int SIMON_ANI_SITDOWN = 3;

constexpr int SIMON_ANI_ATTACK_STANDING = 4;
constexpr int SIMON_ANI_ATTACK_SITDOWN = 5;

constexpr int SIMON_ANI_COLOR = 6;

constexpr int SIMON_ANI_COLOR1 = 7;


constexpr int SIMON_UNTOUCHABLE_TIME = 5000;

class Simon: public GameObject
{
private: 

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
	};

	int ani;
	int untouchable;
	DWORD untouchable_start;
	bool jumped = false;
	bool attacking = false;
	bool checkRewind = false;
	bool throwKatana = false;
	bool isRender = true;

	Whip* whip;
	KatanaWeapon* katanaWeapon;

	std::vector<LPGAMEOBJECT> objectList;
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

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetState(int state);
	~Simon();
};

	