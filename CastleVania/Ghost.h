#pragma once
#include "Enemy.h"

class Ghost : public Enemy
{
	bool isAcTive = false;
public:
	Ghost(D3DXVECTOR2 pos, int width, int height);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void SetState(int state);
	~Ghost();
};

