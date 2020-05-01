#include "Portal.h"
#include "GameObjects/Simon.h"

Portal::Portal(D3DXVECTOR2 pos, EntityID scene_id, int height, int width)
{
	id = ID_ENTITY_PORTAL;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->scene_id = scene_id;
}

void Portal::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void Portal::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void Portal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
}

Portal::~Portal()
{
}
