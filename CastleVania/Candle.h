#pragma once
#include "Candle.h"
#include "GameObjects/GameObject.h"
#include "ResourceManagement.h"
#include "./StaticObject.h"

class Candle : public StaticObject
{
public:
	Candle(D3DXVECTOR2, int height, int width);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~Candle();
};

