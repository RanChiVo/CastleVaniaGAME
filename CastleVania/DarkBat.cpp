#include "DarkBat.h"
#include "ResourceManagement.h"

DarkBat::DarkBat()
{
	id = ID_ENTITY_DARK_BAT;
	AddAnimation(DARK_BAT_IDLE_ANI);
	AddAnimation(DARK_BAT_FLY01_ANI);
	currentAnimation = DARK_BAT_FLY02_ANI;

}

void DarkBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void DarkBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	Enemy::Update(dt, coObjects);
}

void DarkBat::Render(Viewport * viewport)
{
	if (state != STATE_EFFECT)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == -1) flip = normal;
		else flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}

	if (!GameObject::checkInsideViewPort(viewport))
	{
		state = STATE_DETROY;
	}
	Enemy::Render(viewport);
}

void DarkBat::handleState()
{
	switch (state)
	{
	case DARK_BAT_SATE_IDLE:
		break;
	case DARK_BAT_SATE_FLY_01:
		break;
	case DARK_BAT_SATE_FLY_02:
		break;
	}
}

DarkBat::~DarkBat()
{
}
