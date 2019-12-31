#pragma once
#include "Enemy.h"

class DarkBat : public Enemy
{
public:
	enum stateDarkBat
	{
		DARK_BAT_SATE_ACTIVATE,
		DARK_BAT_SATE_IDBLE,
		DARK_BAT_SATE_FLY_01,
		DARK_BAT_SATE_FLY_02,
	};
	DarkBat();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	void handleState();
	~DarkBat();
};

