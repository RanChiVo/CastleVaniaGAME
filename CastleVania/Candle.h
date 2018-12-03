#pragma once
#include "Candle.h"
#include "GameObjects/GameObject.h"
#include "ResourceManagement.h"

class Candle : public GameObject
{
public:
	Candle();

	Candle(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~Candle();
};

