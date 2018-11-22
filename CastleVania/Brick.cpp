#include "Brick.h"
#include "Animations/Animations.h"

CBrick::CBrick()
{
	id = ID_TEX_BRICK;
	/*Animation* ani;
	ani = new Animation(100);		
	ani->Add("brick1");
	Animations::GetInstance()->Add(BRICK_ANI, ani);
	AddAnimation(BRICK_ANI);

	currentAnimation = BRICK_ANI;*/
}

void CBrick::Render(Viewport* viewport)
{/*
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(position.x, position.y);*/
	//RenderBoundingBox(viewport);
}

void CBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CBrick::~CBrick()
{
}
