#pragma once
#include "../GameObjects/GameObject.h"

	constexpr int  MIRACULOUSBAG_STATE_HIDE = 1;
	constexpr int  MIRACULOUSBAG_STATE_SHOW = 2;
	constexpr int  MIRACULOUSBAG_ANI_HIDE = 24;
	constexpr int  MIRACULOUSBAG_ANI_SHOW = 25;
	constexpr float MIRACULOUSBAG_GRAVITY = 0.002f;

class MiraculousBag : public GameObject
{
public:
	MiraculousBag();
	MiraculousBag(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~MiraculousBag();
};

