#include "CastleWall.h"
#include "Animations/Animations.h"
constexpr int CASTLE_ANI = 100;

CastleWall::CastleWall()
{
	Animation* ani;
	ani = new Animation(100);
	ani->Add("CASTLEVANIA_WALL");
	Animations::GetInstance()->Add(CASTLE_ANI, ani);
	AddAnimation(CASTLE_ANI);

	currentAnimation = CASTLE_ANI;
}

void CastleWall::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y - 288));

	animations.find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
}

void CastleWall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}


CastleWall::~CastleWall()
{
}
