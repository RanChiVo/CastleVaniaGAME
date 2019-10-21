#include "BurnBarrel.h"
#include "Simon.h"
#include "Whip.h"
#include "../Animations/Animations.h"
#include "../ResourceManagement.h"


BurnBarrel::BurnBarrel()
{
	id = ID_ENTITY_BURNBARREL;

	AddAnimation(BURNBARREL_ANI);
	currentAnimation = BURNBARREL_ANI;
	nx = 1;
}

void BurnBarrel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	StaticObject::Update(dt, coObjects);
}

void BurnBarrel::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void BurnBarrel::Render(Viewport * viewport)
{
	//RenderBoundingBox(viewport);
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = normal;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	StaticObject::Render(viewport);
}

int BurnBarrel::getCurrentFrame()
{
	return animations.find(currentAnimation)->second->getCurrentFrame();
}

BurnBarrel::~BurnBarrel()
{
}
