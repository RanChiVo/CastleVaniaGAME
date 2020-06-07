#pragma once
#include "Enemy.h"

class VampireBat: public Enemy
{
private:
	int originalLocationY;
	int originalLocationX;
	int delta;
	DWORD timeActivate;
	bool isActive = false;
public:
	enum StateVampireBat
	{
		VAMPIRE_STATE_SLEEP,
		VAMPIRE_STATE_HIDDEN,
		VAMPIRE_STATE_ATTACK,
	};
	VampireBat(D3DXVECTOR2 pos, int height, int width);
	virtual void Render(Viewport* viewport);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
	bool IsActive() { return isActive; }
	void SetIsActive(bool isActive) { this->isActive = isActive; }
	~VampireBat();
};

