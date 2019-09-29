#pragma once
#include "GameObject.h"
#include "../CombatWeapon.h"

constexpr int WHIT_STATE_1 = 1;
constexpr int WHIT_STATE_2 = 2;
constexpr int WHIT_STATE_3 = 3;

class Whip : public CombatWeapon
{
	int type;
	int ani;
	int untouchable;
	DWORD untouchable_start;
	RECT bounding = RECT{0, 0, 0, 0};

public:

	Whip();
	void updatePostision( int currentFrameSimon, int currentAni, int direct);
	int getframe();
	int getCurrentAnimation();
	void Render(Viewport* viewport);
	//bool checkCollision(RECT A, RECT B);
	RECT getBounding();

	void draw(int direct, Viewport* viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	
	~Whip();
};

