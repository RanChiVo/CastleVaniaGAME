#pragma once
#include "GameObject.h"

class Whip : public GameObject
{
	int type;
	int ani;
	int currentAnimationWhip;
public:

	Whip(D3DXVECTOR2 position);
	void draw(int direct);
	void SetPosition(D3DXVECTOR2 position) { x = position.x;  y = position.y; }
	
	~Whip();
};

