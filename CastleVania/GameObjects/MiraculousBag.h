#pragma once
#include "../GameObjects/GameObject.h"

class MiraculousBag : public GameObject
{
public:
	MiraculousBag(EntityID id);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~MiraculousBag();
};

