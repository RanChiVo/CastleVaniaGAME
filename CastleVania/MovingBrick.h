#pragma once
#include "StaticObject.h"

class MovingBrick : public StaticObject
{
	int maxDistance;
	float positionXStart;
	DWORD timeMoving;
public:
	MovingBrick(D3DXVECTOR2 pos, int maxDistance, int height, int  width);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~MovingBrick();
};

