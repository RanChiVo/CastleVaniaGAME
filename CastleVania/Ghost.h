#pragma once
#include "Enemy.h"
#include "BaseInfo.h"

class Ghost : public Enemy
{
	bool isAcTive = false;
	DWORD timeHurt = 0;
public:
	Ghost(D3DXVECTOR2 pos, int width, int height);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void SetState(int state);
	bool IsActive() { return isAcTive; }
	DWORD GetTimeHurt() { return timeHurt; }
	void SetTimeHurt(DWORD timeHurt) { this->timeHurt = timeHurt; }
	~Ghost();
};

