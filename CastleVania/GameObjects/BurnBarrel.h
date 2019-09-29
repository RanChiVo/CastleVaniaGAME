#pragma once
#include "../StaticObject.h"

class BurnBarrel: public StaticObject
{
public:

	BurnBarrel();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) ;
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render( Viewport* viewport);
	int getCurrentFrame();

	~BurnBarrel();
};

