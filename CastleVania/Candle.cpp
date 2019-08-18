#include "Candle.h"


Candle::Candle()
{
	id = ID_TEX_CANDLE;

	LPANIMATION ani;

	AddAnimation(CANDLE_ANI);

	state = CANDLE_STATE_SHOW;

	currentAnimation = CANDLE_ANI;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == CANDLE_STATE_HIDE)
	{
		SetPosition(D3DXVECTOR2(-100, -100));
	}
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + height;
	bottom = y + width;
}

void Candle::Render(Viewport * viewport)
{
	if (state== CANDLE_STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = normal;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else return;
}

Candle::~Candle()
{
}
