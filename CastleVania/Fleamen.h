#pragma once
#include "Enemy.h"

class Fleamen : public Enemy
{
	bool isOnGround = false;
	bool isActive = false;
	bool hasLowJumpedDone = false;
	bool isJumping = false;
	DWORD timeFirstJump = 0;
	DWORD timeLowJump = 0;
	DWORD timeJumpToPlayer = 0;
	DWORD timeOnGround = 0;
public:
	enum StateFleamen
	{
		FLEAMEN_STATE_PREPAIR_ATTACK,
		FLEAMEN_STATE_JUMP_ATTACK,
		FLEAMEN_STATE_JUMP_ON_FLOOR,
		FLEAMEN_STATE_IDLE,
	};

	Fleamen(D3DXVECTOR2 pos, int width, int height);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void SetState(int state);
	void StartActivate();
	void HandleActivateTolLowJump();
	void HandleLowTolHeightJump();
	void HandleHeightToLowJump();

	~Fleamen();
};

