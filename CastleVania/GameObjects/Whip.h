#pragma once
#include "GameObject.h"

constexpr int WHIP_HIT_STAND = 700;
constexpr int WHIT_HIT_SITDOWN = 900;
constexpr int WHIT_HIT_JUMP = 1100;

constexpr int WHIT_ANI_HIT_STAND_RIGHT = 100;
constexpr int WHIT_ANI_HIT_STAND_LEFT = 101;

constexpr int WHIT_ANI_HIT_SITDOWN_RIGHT = 102;
constexpr int WHIT_ANI_HIT_SITDOWN_LEFT = 103;

constexpr int WHIT_ANI_HIT_JUMP_RIGHT = 104;
constexpr int WHIT_ANI_HIT_JUMP_LEFT = 105;

class Whip : public GameObject
{
	int type;
	int ani;
public:

	Whip(D3DXVECTOR2 position);
	void loadResource();
	void draw(int state, int direct);
	void SetPosition(D3DXVECTOR2 position) { x = position.x;  y = position.y; }
	void SetStateWhip(int state); 

	~Whip();
};

