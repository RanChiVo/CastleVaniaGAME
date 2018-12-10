#pragma once
#include "../GameObjects/GameObject.h"

constexpr int STOPWATCH_STATE_HIDE = 1;
constexpr int STOPWATCH_STATE_SHOW = 2;

class StopWatch : public GameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	StopWatch();
	StopWatch(D3DXVECTOR2 position);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~StopWatch();
};

