#pragma once
#include "GameObject.h"

class Entrance : public GameObject
{
	
public:
	Entrance(D3DXVECTOR2 pos);

	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~Entrance();
};

