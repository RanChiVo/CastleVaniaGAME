#pragma once
#include "GameObject.h"

constexpr int BLACKLEOPARD_STATE_IDLE = 1;
constexpr int BLACKLEOPARD_STATE_MOVE_RIGHT = 2;
constexpr int BLACKLEOPARD_STATE_MOVE_LEFT = 3;

class BlackLeopard: public GameObject
{
private:

public:
	BlackLeopard();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void handle();

	~BlackLeopard();
};

