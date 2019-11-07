#pragma once
#include "GameObjects/GameObject.h"

class Item : public GameObject
{
public:
	Item(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	virtual void Render(Viewport* viewport);
	~Item();
};

