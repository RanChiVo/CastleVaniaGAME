#include "Raven.h"
#include "GameObjects/Simon.h"

constexpr float RAVEN_GRAVITY = 0.0009f;
constexpr float RAVEN_SPEED_X = 0.2f;
constexpr float RAVEN_SPEED_Y = 0.1f;
constexpr DWORD RAVEN_TIME_IDLE = 200;

Raven::Raven(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_RAVEN;
	originalLocation_y = pos.y;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	nx = -1;
	SetState(RAVEN_STATE_IDLE);
	timeFly = 300;
}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state!=STATE_EFFECT)
	{
		D3DXVECTOR2 posSimon = Simon::getInstance()->getPosition();

		if (!isActivated) return;

		if (startActiveRandom > 0 && GetTickCount() - startActiveRandom > timeFly)
		{
			startActiveRandom = 0;
		}

		if (startFly > 0 && GetTickCount() - startFly > timeFly)
		{
			startFly = 0;
		}

		if (startFly == 0 && startActiveRandom == 0)
		{
			if ((nx < 0 && x >(posSimon.x - 20)) || (nx > 0 && x < (posSimon.x + 60)))
			{
				if (startIdle == 0 && state != RAVEN_STATE_IDLE)
				{
					startIdle = GetTickCount();
					SetState(RAVEN_STATE_IDLE);
					currentAnimation = RAVEN_ANI_FLY;
				}
				if (startIdle > 0 && GetTickCount() - startIdle > RAVEN_TIME_IDLE)
				{
					startIdle = 0;
					SetState(RAVEN_STATE_FLY);
				}
			}
			else if ((nx < 0 && (x < (posSimon.x - 20))) || (nx > 0 && (x > (posSimon.x + 60))))
			{
				if ( dRandom > 1 && (dRandom % 2 == 0))
				{
					SetState(RAVEN_STATE_FLY);
					SetSpeed(RAVEN_SPEED_X * 2, vy);
					timeFly = 1000;
					nx = -nx;
				}
				else 
				{
					timeFly = 300;
					nx = -nx;
					dRandom += 1;
					SetState(RAVEN_STATE_ACTIVATE);
					if (y >= posSimon.y - 10)
					{
						SetState(RAVEN_STATE_FLY);
					}
				}
			}
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		vector<GameObject*>* simonObject = new vector<GameObject*>();
		simonObject->push_back(Simon::getInstance());
		CalcPotentialCollisions(simonObject, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			float Dx = dx, Dy = dy;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			// block 
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			for (size_t i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult.at(i);
				if (dynamic_cast<Simon*>(e->obj)->isOnGround() &&( nx!=0 || ny!= 0) )
				{
					dynamic_cast<Simon*>(e->obj)->SetState(Simon::SIMON_STATE_HURT);
					state = STATE_EFFECT;
					liveTime = GetTickCount();
				}
			}
		}
		coEvents.clear();
	}

	Enemy::Update(dt, coObjects);
}

void Raven::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Raven::Render(Viewport * viewport)
{
	if (state != STATE_EFFECT && state != STATE_DETROY)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip;

		if (nx == -1) flip = normal;
		else flip = flip_horiz;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}

	if (isActivated && !checkInsideViewPort(viewport) )
	{
		state = STATE_DETROY;
	}

	Enemy::Render(viewport);
}

void Raven::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case RAVEN_STATE_IDLE:
	{
		nx = -1;
		vx = 0;
		vy = 0;
		currentAnimation = RAVEN_ANI_IDLE;
	}
	break;
	case RAVEN_STATE_ACTIVATE:
	{
		startActiveRandom = GetTickCount();
		int activateAreaY = 216 - originalLocation_y;
		int randomPositionY = rand() % (activateAreaY)+originalLocation_y;
		vx = nx * RAVEN_SPEED_X;
		float ytemp = y + 20;
		if (y > Simon::getInstance()->getPosition().y)
		{
			ny = -1;
		}
		else ny = 1;
		vy = ny * (abs(Simon::getInstance()->getPosition().y - ytemp)) / 300;
		currentAnimation = RAVEN_ANI_FLY;
	}
	break;
	case RAVEN_STATE_FLY:
	{
		startFly = GetTickCount();
		vx = nx * RAVEN_SPEED_X;
		vy = 0;
		currentAnimation = RAVEN_ANI_FLY;
	}
	break;
	}
}

void Raven::Activate()
{
	isActivated = true;
	SetState(RAVEN_STATE_ACTIVATE);
}

Raven::~Raven()
{
}
