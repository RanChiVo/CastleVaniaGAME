#pragma once
#include "GameObject.h"

constexpr int BURN_STATE_NOMAL = 1;
constexpr int BURN_STATE_EFFECT = 2;
constexpr int BURN_STATE_HIDE = 3;


class BurnBarrel: public GameObject
{
public:

	BurnBarrel();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) ;
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render( Viewport* viewport);
	int getCurrentFrame();

	~BurnBarrel();
};

