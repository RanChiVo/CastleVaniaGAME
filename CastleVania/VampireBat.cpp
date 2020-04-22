#include "VampireBat.h"
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"

constexpr float VAMPIRE_BAT_SPEED = 0.13f;
constexpr DWORD VAMPIRE_BAT_REVIVAL_TIME = 5000;

VampireBat::VampireBat(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_VAMPIRE_BAT;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	SetState(VAMPIRE_STATE_SLEEP);
	originalLocationX = pos.x - 64;
}

void VampireBat::Render(Viewport * viewport)
{
	if (state!=STATE_EFFECT)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == -1) flip = normal;
		else flip = flip_horiz;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
		Enemy::Render(viewport);
	}

	if (state == VAMPIRE_STATE_HIDDEN)
	{
		if (!checkInsideViewPort(viewport))
		{
			SetState(STATE_DETROY);
		}
	}
}

void VampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	if (state == VAMPIRE_STATE_ATTACK)
	{
		delta += 3.7f;
		y = sin(delta * 3.14 / 180) * 12 + originalLocationY;
	}

	if (timeActivate > 0 && GetTickCount() - timeActivate > VAMPIRE_BAT_REVIVAL_TIME)
	{
		SetState(VAMPIRE_STATE_ATTACK);
	}

	Enemy::Update(dt, coObjects);
}

void VampireBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void VampireBat::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case VAMPIRE_STATE_ATTACK:
		currentAnimation = VAMPIRE_BAT_FLY_ANI1;
		nx = -Simon::getInstance()->get_nx();
		vx = nx * VAMPIRE_BAT_SPEED;
		if (Simon::getInstance()->get_nx() > 0)
		{
			SetPosition(D3DXVECTOR2(Direct3DManager::getInstance()->getViewport()->getEndViewportX(), Simon::getInstance()->getPosition().y));
		}
		else if (Simon::getInstance()->get_nx() < 0)
		{
			SetPosition(D3DXVECTOR2(originalLocationX, Simon::getInstance()->getPosition().y));
		}
		originalLocationY = y;
		timeActivate = GetTickCount();
		break;
	case VAMPIRE_STATE_SLEEP:
		currentAnimation = VAMPIRE_BAT_IDLE_ANI1; 
		timeActivate = 0;
		nx = 1;
		vx = 0;
		vy = 0;
		break;
	case VAMPIRE_STATE_HIDDEN:
		currentAnimation = VAMPIRE_BAT_FLY_ANI1;
		nx = -Simon::getInstance()->get_nx();
		vx = nx * VAMPIRE_BAT_SPEED;
		if (Simon::getInstance()->get_nx() > 0)
		{
			SetPosition(D3DXVECTOR2(Direct3DManager::getInstance()->getViewport()->getEndViewportX(), Simon::getInstance()->getPosition().y));
		}
		else if (Simon::getInstance()->get_nx() < 0)
		{
			SetPosition(D3DXVECTOR2(originalLocationX, Simon::getInstance()->getPosition().y));
		}
		originalLocationY = y;
		break;
	}
}

VampireBat::~VampireBat()
{
}
