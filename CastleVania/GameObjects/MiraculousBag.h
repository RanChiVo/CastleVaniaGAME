#pragma once
#include "../GameObjects/GameObject.h"

	constexpr int  MIRACULOUSBAG_STATE_HIDE = 1;
	constexpr int  MIRACULOUSBAG_STATE_SHOW = 2;

class MiraculousBag : public GameObject
{
public:
	MiraculousBag();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~MiraculousBag();
};

