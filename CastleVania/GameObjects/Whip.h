#pragma once
#include "GameObjects/GameObject.h"

class Whip : public GameObject
{
	int type;



public:
	Whip();

	void loadResource();
	void Update(DWORD dt);
	void Render();

	~Whip();
};

