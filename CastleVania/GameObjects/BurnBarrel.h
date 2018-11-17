#pragma once
#include "GameObject.h"

class BurnBarrel: public GameObject
{
	int untouchable;
	DWORD untouchable_start;

public:
	BurnBarrel();
	BurnBarrel(D3DXVECTOR2 position);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render( Viewport* viewport);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	~BurnBarrel();
};

