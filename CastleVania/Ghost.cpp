#include "Ghost.h"
#include "GameObjects/Simon.h"

constexpr float GHOST_SPEED_X = 0.07f;
constexpr float GHOST_SPEED_Y = 0.065f;
constexpr int GHOST_DISTANCE_NEAR_SIMON = 50;
constexpr DWORD GHOST_TIME_HURT = 50;

Ghost::Ghost(D3DXVECTOR2 pos, int width, int height)
{
	id = ID_ENTITY_GHOST;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	currentAnimation = GHOST_ANI;
	SetState(STATE_HIDDEN);
	baseInfo = new BaseInfo();
	baseInfo->setHealth(2);
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	if (baseInfo->getHealth() == 0 && state != STATE_EFFECT)
	{
		SetState(STATE_EFFECT);
		setLiveTime(GetTickCount());
	}

	if (timeHurt > 0 && GetTickCount() - timeHurt > GHOST_TIME_HURT)
	{
		timeHurt = 0;
		baseInfo->setHealth(max(0, baseInfo->getHealth() - 1));
	}

	if (state==STATE_SHOW)
	{
		Simon* simon = Simon::getInstance();
		
		if (!isAcTive && x < simon->getPosition().x - GHOST_DISTANCE_NEAR_SIMON)
		{
			nx = 1;
			isAcTive = true;
		}

		if (isAcTive)
		{
			if (x > simon->getPosition().x + simon->getWidth()/2 + GHOST_DISTANCE_NEAR_SIMON)
			{
				nx = -1;
				vx = -GHOST_SPEED_X;
				vy = -GHOST_SPEED_Y;

			}
			else if (x < simon->getPosition().x - GHOST_DISTANCE_NEAR_SIMON)
			{
				nx = 1;
				vx = GHOST_SPEED_X;
				vy = -GHOST_SPEED_Y;
			}
		}

		if (y < simon->getPosition().y + 15)
		{
			vy = GHOST_SPEED_Y;
		}
		else if (y > simon->getPosition().y)
		{
			vy = -GHOST_SPEED_Y;
		}
	}

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
	if (isAcTive && !checkInsideViewPort(viewport))
	{
		SetState(STATE_DETROY);
	}
}

void Ghost::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
		case STATE_SHOW:
		{
			currentAnimation = GHOST_ANI;
			Viewport * viewport = Direct3DManager::getInstance()->getViewport();
			float xNew = viewport->getX() + viewport->getWidth();
			SetPosition(D3DXVECTOR2(xNew, viewport->getY() + viewport->getHeight()));
			vy = GHOST_SPEED_Y;
			vx =-GHOST_SPEED_X;
			nx = -1;
		}
		break;
		case STATE_HIDDEN:
		{
			vx = 0;
			vy = 0;
		}
		break;
	}
}

Ghost::~Ghost()
{
}
