#pragma once
#include "StaticObject.h"

class PortalPosMap :public StaticObject
{
	float startViewportX;
	float endViewportX;
	float startViewportY;

public:
	PortalPosMap(D3DXVECTOR2 pos, int height, int width, float startViewportX, float endViewportX, float startViewportY);
	float GetStartViewportX() { return startViewportX; }
	float GetEndViewportX() { return endViewportX; }
	float GetStartViewportY() { return startViewportY; }

	void SetStartViewportX(float startViewportX) { this->startViewportX = startViewportX; }
	void SetEndViewportX(float endViewportX) { this->endViewportX = endViewportX; }
	void SetStartViewportY(float startViewportY) { this->startViewportY = startViewportY; }

	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	~PortalPosMap();
};

