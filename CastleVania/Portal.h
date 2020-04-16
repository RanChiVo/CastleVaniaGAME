#pragma once
#include "StaticObject.h"

class Portal : public StaticObject
{
	EntityID scene_id;

public:
	Portal(D3DXVECTOR2 pos, EntityID scene_id, int height, int width);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	EntityID GetSceneId() { return scene_id; }
	~Portal();
};

