#include "../GameObjects/GameObject.h"

#pragma once
class MiraculousBag : public GameObject
{
private:
	int startMoneyEffectTime = 0;
public:
	MiraculousBag(EntityID id, D3DXVECTOR2 pos);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~MiraculousBag();
};

