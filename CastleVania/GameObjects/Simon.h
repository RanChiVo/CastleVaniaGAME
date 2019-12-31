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
	int ani;
	int untouchable;
	DWORD untouchable_start;
	DWORD comeEntranceStart = 0;
	DWORD invisible_Potion_Start = 0;
	bool isInSpawn = false;
	EntityID idEnemySpawn;
	bool enableSubWeapon = false;
	bool isjumping = false;
	bool attacking = false;
	bool checkRewind = false;
	bool isOnStair = false;
	bool hasMovedMap = false;
	bool isInTunel = false;
	bool isVisible = false;
	bool isMovingDoor = false;
	DWORD startAtack = 0;
	DWORD startAtackSub= 0;
	DWORD startHurt;
	ObjectStair* originalStair = nullptr;
	ObjectStair* reverseStair = nullptr;
	Flip flip;

	Whip* whip;
	int levelWhip;
	int WHIP_STATE;
	int startThrowWeapon = 0;
	BaseInfo* baseInfo;
	std::vector<LPGAMEOBJECT> objectCollision;
	static Simon* _instance;
	Simon();
public:
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
		SIMON_STATE_ATTACK_UP_STAIR,
		SIMON_STATE_ATTACK_DOWN_STAIR,
		SIMON_STATE_HURT,
	};

	static Simon* getInstance();
	virtual void loadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	BaseInfo* getBaseInfo() { return baseInfo; }
	ObjectStair*  getOriginalStair() { return originalStair; }
	bool isMovedMap();
	void SetStateMoveMap(bool hasMovedMap);
	bool IsInTunel() { return isInTunel; }
	void setInTunel(bool isInTunel) { this->isInTunel = isInTunel; }
	bool isOnGround();
	bool IsOnStair() { return isOnStair; }
	void SetIsOnStair(bool isOnStair){}
	bool IsMovingDoor() { return isMovingDoor; }
	void setIsMovingDoor(bool isMovingDoor) {this->isMovingDoor = isMovingDoor;}
	int GetLevel() { return level; }
	void SetState(int state);
	bool checkisInSpawn() { return isInSpawn; }
	void setIsInSpawn(bool isInSpawn) { this->isInSpawn = isInSpawn; }
	EntityID getIdEnemySpawn() { return idEnemySpawn; }
	void setIdEnemySpawn(EntityID idEnemySpawn) { this->idEnemySpawn = idEnemySpawn; }
	void Reset(int currentAnimation);
	void handleState();
	void updateCollisionStair();
	void updateCollisionSubStair();
	void Simon::handleOutOfStair();
	void handleCollisionObjectGame(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void handleAfterCollision(vector<LPGAMEOBJECT> *coObjects, EntityID id ,int i, vector<LPCOLLISIONEVENT> *coEvents);
	void handleCollisionIntersectedObject(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void RemoveWhip();
	void SetupAtacking();
	void SetupSubWeapon(vector<LPGAMEOBJECT> *coObjects);
	void RenderWeapon(LPANIMATION animation, Viewport* viewport);
	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	void OnKeyStateChange(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void moveRight(DWORD dt);
	~Simon();
};

	