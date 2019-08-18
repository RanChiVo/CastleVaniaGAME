#include "BurnBarrel.h"
#include "Simon.h"
#include "Whip.h"
#include "../Animations/Animations.h"
#include "../ResourceManagement.h"


BurnBarrel::BurnBarrel()
{
	id = ID_TEX_BURNBARREL;

	AddAnimation(BURNBARREL_ANI);
	AddAnimation(ANI_EFFECT);

	state = BURN_STATE_NOMAL;
	currentAnimation = BURNBARREL_ANI;
	nx = 1;
}

void BurnBarrel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (state == BURN_STATE_HIDE)
	{
		SetPosition(D3DXVECTOR2(-100, -100));
	}
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
	if (state == BURN_STATE_NOMAL)
	{
	//	RenderBoundingBox(viewport);

		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = normal;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else return;

}

int BurnBarrel::getCurrentFrame()
{
	return animations.find(currentAnimation)->second->getCurrentFrame();
}

BurnBarrel::~BurnBarrel()
{
}
