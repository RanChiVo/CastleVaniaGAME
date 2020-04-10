 #pragma once
#include "GameObjects/GameObject.h"

class Pork_Chop : public GameObject
{
public:
	Pork_Chop(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~Pork_Chop();
};

