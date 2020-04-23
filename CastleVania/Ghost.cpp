#include "Ghost.h"
constexpr float GHOST_SPEED = 0.13f;
#include "GameObjects/Simon.h"


Ghost::Ghost(D3DXVECTOR2 pos, int maxDistance, int width, int height)
{
	id = ID_ENTITY_GHOST;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	currentAnimation = GHOST_ANI;
	SetState(STATE_SHOW);
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Ghost::Render(Viewport * viewport)
{
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == -1) flip = normal;
		else flip = flip_horiz;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
		Enemy::Render(viewport);
	}
}

void Ghost::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case STATE_SHOW:
		currentAnimation = GHOST_ANI;
		Simon* simon = Simon::getInstance();
		set_nx(simon->get_nx());
		vx = nx * GHOST_SPEED;
	
		liveTime = GetTickCount();
		break;
	case STATE_HIDDEN:
		vx = 0; 
		vy = 0;
		break;
	}
}

Ghost::~Ghost()
{
}
