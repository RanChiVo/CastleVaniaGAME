#pragma once
#include "Candle.h"
#include "GameObjects/GameObject.h"
#include "ResourceManagement.h"

constexpr int CANDLE_STATE_HIDE = 1;
constexpr int CANDLE_STATE_SHOW = 2;


class Candle : public GameObject
{
public:
	Candle();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~Candle();
};

