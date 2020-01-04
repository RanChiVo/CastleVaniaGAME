#pragma once
#include "GameObjects/GameObject.h"

class Axe : public GameObject
{
public:
	Axe(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~Axe();
};

