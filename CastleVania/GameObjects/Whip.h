#pragma once
#include "GameObject.h"
constexpr int WHIT_STATE_1 = 1;
constexpr int WHIT_STATE_2 = 2;
constexpr int WHIT_ANI_HIT_RIGHT1 = 14;
constexpr int WHIT_ANI_HIT_LEFT1 = 15;
constexpr int WHIT_ANI_HIT_RIGHT2 = 16;
constexpr int WHIT_ANI_HIT_LEFT2 = 17;

class Whip : public GameObject
{
	int type;
	int ani;
	int untouchable;
	DWORD untouchable_start;
	RECT bounding = RECT{0, 0, 0, 0};

public:

	Whip(D3DXVECTOR2 position);
	void updatePostision( int currentFrameSimon, int currentAni);
	int getframe();
	int getCurrentAnimation();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* ObjectList, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Viewport* viewport);
	bool checkCollision(RECT A, RECT B);
	RECT getBounding();

	void draw(int direct, Viewport* viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	
	~Whip();
};

