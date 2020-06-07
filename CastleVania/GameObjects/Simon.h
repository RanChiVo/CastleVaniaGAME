#pragma once
#include "../GameObjects/GameObject.h"
#include "../Animations/Animation.h"
#include "../GameObjects/Whip.h"
#include "../DaggerWeapon.h"
#include "../CombatWeapon.h"
#include "../BaseInfo.h"
#include "../ObjectStair.h"
#include "Floor.h"
#include "../Portal.h"

class Simon: public GameObject
{
private: 
	int ani;
	int untouchable;
	DWORD untouchable_start;
	DWORD comeEntranceStart = 0;
	DWORD invisible_Potion_Start = 0;
	bool isInSpawn = false;
	D3DXVECTOR2 startPosPlayer;
	std::string activateNameEnemy;
	EntityID idEnemySpawn;
	bool enableSubWeapon = false;
	bool isjumping = false;
	bool attacking = false;
	bool checkRewind = false;
	bool isOnStair = false;
	bool isVisible = false;
	bool OnGround = false;
	bool isGoingAutoStair = false;
	int temporaryState;
	bool isJumpingFloor = false;
	bool isDie = false;

	DWORD timeAtack = 0;
	DWORD timeAttackOneShot = 0;
	DWORD timeAttackDoubleShot = 0;
	DWORD timeAtackSub= 0;
	DWORD timeHurt;
	DWORD timeDie = 0;
	DWORD timeChangeColor = 0;
	DWORD timeJumpHeightFloor = 0;
	DWORD timeSitAfterJump = 0;
	DWORD timeThrowWeapon = 0;
	DWORD timeAutoGoStair = 0;
	DWORD startJumpingSitFloor;
	DWORD startJumpingFloor;
	ObjectStair* originalStair = nullptr;
	D3DXVECTOR2 resetPosition;
	GameObject* highFloor = nullptr; 
	GameObject* itemSub = nullptr; 
	Portal *p = nullptr;
	Flip flip;
	Whip* whip;
	int levelWhip;
	int WHIP_STATE;
	int changeColorId = 1;
	BaseInfo* baseInfo;
	static Simon* _instance;
	Simon();
public:
	enum State
	{
		SIMON_STATE_IDLE,
		SIMON_STATE_WALKING_RIGHT,
		SIMON_STATE_WALKING_LEFT,
		SIMON_STATE_JUMPING,
		SIMON_STATE_SITDOWN,
		SIMON_STATE_ATTACK_STAND,
		SIMON_STATE_ATTACK_STAND_SUBWEAPON,
		SIMON_STATE_ATTACK_SITDOWN,
		SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON,
		SIMON_STATE_DIE,
		SIMON_STATE_CHANGECOLOR,
		SIMON_STATE_GO_UP_STAIR,
		SIMON_STATE_GO_DOWN_STAIR,
		SIMON_STATE_IDLE_UP_STAIR,
		SIMON_STATE_IDLE_DOWN_STAIR,
		SIMON_STATE_ATTACK_UP_STAIR,
		SIMON_STATE_ATTACK_UP_STAIR_SUPWEAPON,
		SIMON_STATE_ATTACK_DOWN_STAIR,
		SIMON_STATE_HURT,
		SIMON_STATE_AUTO_GOES,
		SIMON_STATE_WIN,
		SIMON_STATE_WIN_FINISH,
	};

	static Simon* getInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	BaseInfo* getBaseInfo() { return baseInfo; }
	ObjectStair*  getOriginalStair() { return originalStair; }
	void setActivateEnemyName(std::string nameEnemy) { this->activateNameEnemy = nameEnemy; }
	std::string getActivateEnemyName() { return activateNameEnemy; }
	bool isOnGround();
	bool IsOnStair() { return isOnStair; }
	void SetIsOnStair(bool isOnStair){}
	void SetState(int state);
	bool checkisInSpawn() { return isInSpawn; }
	void setIsInSpawn(bool isInSpawn) { this->isInSpawn = isInSpawn; }
	EntityID getIdEnemySpawn() { return idEnemySpawn; }
	void setIdEnemySpawn(EntityID idEnemySpawn) { this->idEnemySpawn = idEnemySpawn; }
	void Reset(int currentAnimation);
	void updateCollisionSubStair();
	void Simon::handleOutOfStair();
	void handleCollisionObjectGame(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void handleAfterCollision(vector<LPGAMEOBJECT> *coObjects, EntityID id ,int i, vector<LPCOLLISIONEVENT> *coEvents);
	void handleCollisionIntersectedObject(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> *coEvents);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void Reset();
	void setResetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 getResetPosition() { return resetPosition; }

	void SetWhip(Whip* whip) { this->whip = whip; }
	void SetupAtacking();
	void SetupSubWeapon(vector<LPGAMEOBJECT> *coObjects);
	void RenderWeapon(LPANIMATION animation, Viewport* viewport);
	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetTimeAttack(DWORD time) { this->timeAtack = time; }
	void SetTimeAttackSub(DWORD time) { this->timeAtackSub = time; }
	DWORD GetTimeAttack() { return timeAtack; }
	DWORD GetTimeAttackSub() { return timeAtackSub; }
	DWORD GetTimeJumpingSitFloor() { return startJumpingSitFloor; }
	DWORD GetTimestartJumpingFloor() { return startJumpingFloor; }
	DWORD GetTimeUntouchable() { return untouchable_start; }
	DWORD GetTimeAttackOneShot() { return timeAttackOneShot; }
	DWORD GetTimeAttackDoubleShot() { return timeAttackDoubleShot; }
	void SetTimeAttackDoubleShot(DWORD time) { this->timeAttackDoubleShot = time; }
	void SetTimeAttackOneShot(DWORD time) { this->timeAttackOneShot = time; }

	D3DXVECTOR2 GetStartPosPlayer() { return startPosPlayer; }
	void SetStartPosPlayer(D3DXVECTOR2 pos) { this->startPosPlayer = pos; }

	void AutoGoUpStair(State state );
	void UpdateGotoStair();
	bool IsGoingAutoStair() { return isGoingAutoStair; }
	void LoadWhip();
	void UnloadWhip();
	Portal* GetPortal() { return p; }
	void SetPortal(Portal* p) { this->p = p; }
	bool IsDie(){return isDie;}
	void SetIsDie(bool isDie) { this->isDie = isDie; }
	GameObject* GetHightFloor() { return highFloor; }
	~Simon();
};

	