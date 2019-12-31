#pragma once
#include "GameObjects/GameObject.h"

class ObjectMoveMap : public GameObject
{
public:
	ObjectMoveMap();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~ObjectMoveMap();
};

