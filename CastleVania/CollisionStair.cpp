#include "CollisionStair.h"



CollisionStair::CollisionStair(D3DXVECTOR2 position)
{
	id = ID_COLLISION_STAIR;
	x = position.x;
	y = position.y;
}

void CollisionStair::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void CollisionStair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CollisionStair::~CollisionStair()
{
}
