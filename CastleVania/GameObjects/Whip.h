#pragma once
#include "GameObject.h"

class Whip : public GameObject
{
	int type;
	int ani;
public:
	int getCurrentFrame();
	Whip(D3DXVECTOR2 position);
	void updatePostision(D3DXVECTOR2 position, int currentFrameSimon);
	void draw(int direct, Viewport* viewport);
	
	~Whip();
};

