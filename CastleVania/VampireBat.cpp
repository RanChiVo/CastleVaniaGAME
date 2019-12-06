#include "VampireBat.h"
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"

constexpr float VAMPIRE_BAT_SPEED = 0.13f;
constexpr DWORD VAMPIRE_BAT_REVIVAL_TIME = 6000;

VampireBat::VampireBat()
{
	id = ID_ENTITY_VAMPIRE_BAT;
	state = VAMPIRE_STATE_HIDDEN;
	
	AddAnimation(VAMPIRE_BAT_IDLE_ANI1);
	AddAnimation(VAMPIRE_BAT_FLY_ANI1);
	currentAnimation = VAMPIRE_BAT_IDLE_ANI1;
	originalLocationY = y;
	delta = 0;
	nx = 1;
	vx = nx * VAMPIRE_BAT_SPEED;
	timeActivate = 0;
}

void VampireBat::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	RenderBoundingBox(viewport);
	Flip flip;
	if (nx == -1) flip = normal;
	else flip = flip_horiz;
	if ( state == STATE_SHOW)
	{
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
}

void VampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	handleState();
	x += dx;
	if (state == VAMPIRE_STATE_HIDDEN)
	{
		if (Simon::getInstance()->checkisInSpawn() && Simon::getInstance()->getIdEnemySpawn() == id && timeActivate == 0)
		{
			timeActivate = GetTickCount();
			state = STATE_SHOW;
			nx = -Simon::getInstance()->get_nx();
			vx = nx * VAMPIRE_BAT_SPEED;
			if (Simon::getInstance()->get_nx() > 0)
			{
				SetPosition(D3DXVECTOR2(Direct3DManager::getInstance()->getViewport()->getX() +
					Direct3DManager::getInstance()->getViewport()->getWidth(), Simon::getInstance()->getPosition().y));
			}
			else if (Simon::getInstance()->get_nx() < 0)
			{
				SetPosition(D3DXVECTOR2(Direct3DManager::getInstance()->getViewport()->getX(), Simon::getInstance()->getPosition().y));
			}
			originalLocationY = y;
		}
	}
	
	if (state == STATE_SHOW)
	{
		if (GetTickCount()- timeActivate > VAMPIRE_BAT_REVIVAL_TIME)
		{
			SetState(VAMPIRE_STATE_HIDDEN);
			timeActivate = 0;
		}
	}
	
	if (state != STATE_EFFECT)
	{
		delta += 3.7f;
		y = sin(delta * 3.14 / 180) * 12 + originalLocationY;
	}
	Enemy::Update(dt, coObjects);
}

void VampireBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == STATE_SHOW)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
}

void VampireBat::handleState()
{
	switch (state)
	{
	case STATE_SHOW:
		currentAnimation = VAMPIRE_BAT_FLY_ANI1;
		break;
	}
}

VampireBat::~VampireBat()
{
}
