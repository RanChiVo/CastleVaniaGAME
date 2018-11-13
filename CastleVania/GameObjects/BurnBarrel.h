#pragma once
#include "GameObject.h"

class BurnBarrel: public GameObject
{
public:

	BurnBarrel(D3DXVECTOR2 position);
	void Render( Viewport* viewport);

	~BurnBarrel();
};

