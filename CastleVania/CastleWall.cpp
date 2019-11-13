#include "CastleWall.h"
#include "Animations/Animations.h"

CastleWall::CastleWall()
{
	id = ID_ENTITY_CASTLEVANIA_WALL;
	AddAnimation(CASTLE_ANI);
	currentAnimation = CASTLE_ANI;
}

void CastleWall::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	animations.find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
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
