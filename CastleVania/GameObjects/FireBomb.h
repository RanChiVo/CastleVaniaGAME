#pragma once
#include "GameObject.h"
class FireBomb : public GameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	
	FireBomb(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~FireBomb();
};

