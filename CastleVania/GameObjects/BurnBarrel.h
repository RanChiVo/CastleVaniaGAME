#pragma once
#include "GameObject.h"

constexpr int BURNBARREL_STATE_NORMAL = 1;
constexpr int BURNBARREL_STATE_EFFECT = 2;


class BurnBarrel: public GameObject
{
public:

	BurnBarrel();
	BurnBarrel(D3DXVECTOR2 position);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) ;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render( Viewport* viewport);
	int getCurrentFrame();

	~BurnBarrel();
};

