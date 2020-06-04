#pragma once
#include "Enemy.h"

class Raven : public Enemy 
{
private:
	float originalLocation_y;
	DWORD startActiveRandom = 0;
	DWORD startFly = 0;
	DWORD startIdle = 0;
	DWORD timeFly;
	bool isActivated = false;
	int dRandom = 0;
public:
	enum stateRaven
	{
		RAVEN_STATE_IDLE,
		RAVEN_STATE_ACTIVATE,
		RAVEN_STATE_FLY,
	};
	Raven(D3DXVECTOR2 pos, int height, int width);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void SetState(int state);
	void Activate();
	~Raven();
};

