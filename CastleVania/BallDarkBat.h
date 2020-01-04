#pragma once
#include "GameObjects/GameObject.h"

class BallDarkBat:public GameObject
{
	DWORD startUntouched = 0;
public:
	BallDarkBat( D3DXVECTOR2 pos);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~BallDarkBat();
};

