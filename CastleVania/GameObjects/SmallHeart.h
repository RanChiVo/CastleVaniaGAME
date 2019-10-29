#pragma once
#include "../GameObjects/GameObject.h"

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

			