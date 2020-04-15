#include "Candle.h"


Candle::Candle()
{
	id = ID_ENTITY_CANDLE;
	//AddAnimation(CANDLE_ANI);
	currentAnimation = CANDLE_ANI;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	StaticObject::Update(dt, coObjects);
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
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = normal;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	StaticObject::Render(viewport);
}

Candle::~Candle()
{
}
