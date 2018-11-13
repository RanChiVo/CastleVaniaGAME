#pragma once
#include "GameObject.h"

class Whip : public GameObject
{
	int type;
	int ani;
public:

	Whip(D3DXVECTOR2 position);
	void draw(int direct, Viewport* viewport);
	
	~Whip();
};

