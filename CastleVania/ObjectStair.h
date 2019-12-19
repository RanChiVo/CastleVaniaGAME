#include "StaticObject.h"

#pragma once
class ObjectStair :public StaticObject
{
	float bboxHeight;
	float bboxWidth;
	D3DXVECTOR4 infoStair{ bboxHeight, bboxWidth, nx , ny };
public:
	ObjectStair(D3DXVECTOR2 pos, D3DXVECTOR4 infoStair, int height);
	ObjectStair(ObjectStair* o);
	D3DXVECTOR4 getInfoStair() { return infoStair; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~ObjectStair();
};

