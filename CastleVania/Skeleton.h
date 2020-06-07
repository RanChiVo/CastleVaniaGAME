#pragma once
#include "Enemy.h"
#include "Bone.h"

class Skeleton : public Enemy
{
	bool isOnGround = false;
	bool isActive = false;
	bool isActiveFirst = false;
	bool isJumping = false;
	int nxOrginal = 1;
	float XOrginal = 0;
	float YOrginal = 0;
	float XorginalSimon = 0;
	float nx_Render = 0;
	int distanceMoving;
	int XGoOutActivateArea;
	bool isAttack;
	DWORD timemoving = 0;
	DWORD timeActivate = 0;
	DWORD startmoving = 0;
	DWORD startAttack = 0;
	DWORD startConsecutiveAttack = 0;
	int direct = 1;
	vector<Bone*> weaponWhiteSkeleton;
public:
	enum StateSkeleton {
		SKELETON_STATE_ACTIVE,
		SKELETON_STATE_JUMP_LEFT,
		SKELETON_STATE_JUMP_RIGHT,
	};
	Skeleton(D3DXVECTOR2 pos, int nx, int height, int width);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void SetActivate(bool isActive);
	bool IsActive() { return isActive; }
	void SetState(int state);
	void SetDistanceGoOutActivateArea(int distance) { this->XGoOutActivateArea = distance; }
	void Reset();
	DWORD RandomNumber(DWORD time1, DWORD time2);
	~Skeleton();
};

