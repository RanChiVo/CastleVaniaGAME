#pragma once
#include "GameObject.h"

class BurnBarrel: public GameObject
{
public:
	BurnBarrel();
	BurnBarrel(D3DXVECTOR2 position);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render( Viewport* viewport);

	~BurnBarrel();
};

