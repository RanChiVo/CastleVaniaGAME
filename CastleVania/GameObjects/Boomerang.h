#pragma once
#include "../GameObjects/GameObject.h"

constexpr int BOOMERANG_STATE_HIDE = 1;
constexpr int BOOMERANG_STATE_SHOW = 2;

class Boomerang : public GameObject
{
	int untouchable;
	DWORD untouchable_start;
	
public:
	Boomerang(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~Boomerang();
};

