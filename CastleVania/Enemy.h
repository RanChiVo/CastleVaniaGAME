#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

class Enemy : public GameObject
{
protected:
	EntityID idHiddenItem;
	DWORD timeRevival;
	static DWORD stopWatchStart;
public:
	Enemy();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state) { this->state = state; }
	virtual void setTimeRevival(DWORD timeRevival);
	static void StopWatchStart();
	virtual DWORD getTimeRevival(DWORD timeRevival);

	~Enemy();
};

