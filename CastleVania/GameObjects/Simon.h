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
	bool isInSpawn = false;
	EntityID idEnemySpawn;
	bool enableSubWeapon = false;
	bool isjumping = false;
	bool attacking = false;
	bool checkRewind = false;
	bool isOnStair = false;
	int directionStair;
	float positition_stair;
	bool hasMovedMap = false;
	bool isInTunel = false;
	ObjectStair* originalStair = nullptr;
	ObjectStair* reverseStair = nullptr;
	Flip flip;

	std::string stair_direction;
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


	bool isMovedMap();
	void SetStateMoveMap(bool hasMovedMap);
	bool IsInTunel() { return isInTunel; }
	void setInTunel(bool isInTunel) { this->isInTunel = isInTunel; }
	bool isOnGround();
	int GetLevel() { return level; }
	void SetState(int state);
	bool checkisInSpawn() { return isInSpawn; }
	void setIsInSpawn(bool isInSpawn) { this->isInSpawn = isInSpawn; }
	EntityID getIdEnemySpawn() { return idEnemySpawn; }
	void setIdEnemySpawn(EntityID idEnemySpawn) { this->idEnemySpawn = idEnemySpawn; }
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
	void moveRight(DWORD dt);
	~Simon();
};

	