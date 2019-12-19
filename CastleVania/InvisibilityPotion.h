#pragma once
#include "GameObjects/GameObject.h"

class InvisibilityPotion: public GameObject
{
public:
	InvisibilityPotion(D3DXVECTOR2 pos);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~InvisibilityPotion();
};

