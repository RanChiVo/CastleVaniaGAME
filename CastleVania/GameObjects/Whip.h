#pragma once
#include "GameObject.h"

class Whip : public GameObject
{
	int type;

	enum stateHIT
	{
		WHIP_HIT_STAND,
		WHIT_HIT_SITDOWN,
		WHIT_HIT_JUMP,
	};


public:
	Whip();

	void Innitialize();
	void loadResource();
	void handleState();
	void Update(D3DXVECTOR2 position);
	void SetPosition(D3DXVECTOR2 position) { x = position.x;  y = position.y; }
	void SetStateWhip(int state); 

	~Whip();
};

