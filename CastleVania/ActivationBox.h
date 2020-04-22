#pragma once
#include "StaticObject.h"

class ActivationBox:public StaticObject
{
	EntityID activatedObjecId;
	bool isActivate;

public:
	ActivationBox(D3DXVECTOR2 pos, EntityID activatedObjecId, int height, int width);
	void ActionObject(vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	EntityID GetActivatedObjecId() { return activatedObjecId; }
	void SetActivatedObjecId(EntityID activatedObjecId) { this->activatedObjecId= activatedObjecId; }

	~ActivationBox();
};

