#pragma once
#include "GameObject.h"

class Whip : public GameObject
{
	int type;
	int ani;
public:

	Whip(D3DXVECTOR2 position);
	void updatePostision( int currentFrameSimon, int currentAni);
	int getframe();
	int getCurrentAnimation();
	void draw(int direct, Viewport* viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	
	~Whip();
};

