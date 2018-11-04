#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
private: 

	RECT boundingBox;

public:
	Wall(int l, int t, int r, int b);
	RECT getBounding();

	~Wall();
};

