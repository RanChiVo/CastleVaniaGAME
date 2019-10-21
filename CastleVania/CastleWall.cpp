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
	animations.find(currentAnimation)->second->Render(x, y, Flip::normal);
}

void CastleWall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

CastleWall::~CastleWall()
{
}
