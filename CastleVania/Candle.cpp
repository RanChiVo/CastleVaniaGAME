#include "Candle.h"


Candle::Candle(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_CANDLE;
	SetPosition(pos);
	setHeight(height);
	setWidth(width);
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
	right = x + width;
	bottom = y + height;
}

void Candle::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
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
