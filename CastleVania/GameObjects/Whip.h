#pragma once
#include "GameObject.h"

class Whip : public GameObject
{
	int type;
	int ani;
public:

	Whip(D3DXVECTOR2 position);
	void updatePostision(D3DXVECTOR2 position, int currentFrameSimon, int currentAni);
	int getframe();
	void draw(int direct, Viewport* viewport);
	
	~Whip();
};

