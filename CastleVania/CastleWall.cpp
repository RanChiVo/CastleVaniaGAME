#include "CastleWall.h"

CastleWall::CastleWall(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_CASTLEVANIA_WALL;
	this->height = height;
	this->width = width;
	SetPosition(pos);
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(id);
	SetAnimationSet(ani_set);
	currentAnimation = CASTLE_ANI;
}

void CastleWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CastleWall::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
}

void CastleWall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CastleWall::~CastleWall()
{
}
