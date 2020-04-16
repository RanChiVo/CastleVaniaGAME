#pragma once
#include "Enemy.h"

class VampireBat: public Enemy
{
private:
	int originalLocationY;
	int delta;
	DWORD timeActivate;
public:
	enum StateVampireBat
	{
		VAMPIRE_STATE_SLEEP,
		VAMPIRE_STATE_HIDDEN,
	};
	VampireBat(D3DXVECTOR2 pos, int height, int width);
	virtual void Render(Viewport* viewport);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void handleState();
	~VampireBat();
};

