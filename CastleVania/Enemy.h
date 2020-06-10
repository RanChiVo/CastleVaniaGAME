#pragma once
#include "../CastleVania/GameObjects/GameObject.h"
#include "BaseInfo.h"

class Enemy : public GameObject
{
protected:
	EntityID idHiddenItem;
	DWORD timeRevival;
	static DWORD stopWatchStart;
	BaseInfo* baseInfo;
public:
	Enemy();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state) { this->state = state; }
	virtual void setTimeRevival(DWORD timeRevival);
	static void StopWatchStart();
	virtual DWORD getTimeRevival(DWORD timeRevival);
	BaseInfo* GetBaseInfo() { return baseInfo; }
	~Enemy();
};

