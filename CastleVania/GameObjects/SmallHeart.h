#pragma once
#include "../GameObjects/GameObject.h"

constexpr int SMALL_HEART_STATE_HIDE = 1;
constexpr int SMALL_HEART_STATE_SHOW = 2;

class SmallHeart :public GameObject
{
	int untouchable;
	int originalLocation;
	float specifications;
	float delta;
	DWORD untouchable_start;

public:
	SmallHeart(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void movement();
	~SmallHeart();
};

			