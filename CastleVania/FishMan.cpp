#include "FishMan.h"
#include "ResourceManagement.h"
#include "./CrystalBall.h"
#include "./WaterEffect.h"

constexpr float FISH_MAN_GRAVITY = 0.001f;
constexpr float FISH_MAN_SPEED_WALK = 0.12f;
constexpr float FISH_MAN_SPEED_JUMP = 0.7f;
constexpr DWORD  FISH_MAN_SHOOT = 500;
constexpr DWORD  FISH_MAN_WALK = 1000;
constexpr DWORD  FISH_MAN_REVIVAL_TIME = 6000;

FishMan::FishMan(D3DXVECTOR2 position)
{
	id = ID_ENTITY_FISH_MAN;
	state = FISH_MAN_STATE_HIDDEN;
	AddAnimation(FISH_MAN_ANI_IDLE);
	AddAnimation(FISH_MAN_ANI_WALK);
	AddAnimation(FISH_MAN_ANI_SHOOT);
	currentAnimation = FISH_MAN_ANI_IDLE;
	posRevival = position;
	vx = 0;
	timeRevival = 0;
	simon = Simon::getInstance();
}

void FishMan::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	RenderBoundingBox(viewport);
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	if (state != FISH_MAN_STATE_HIDDEN)
	{
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
}

void FishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	handleState();

	if (state!= FISH_MAN_STATE_HIDDEN)
	{
		vy += FISH_MAN_GRAVITY * dt;
	}

	if (state == FISH_MAN_STATE_HIDDEN)
	{
		if( Simon::getInstance()->checkisInSpawn() && Simon::getInstance()->getIdEnemySpawn() == id && timeRevival == 0)
		{
			timeRevival = GetTickCount();
			SetState(FISH_MAN_STATE_IDLE);
			vy = -FISH_MAN_SPEED_JUMP;
			WaterEffect* effect = new WaterEffect(getPosition());
			coObjects->push_back(effect);

		}
	}

	if (state != FISH_MAN_STATE_HIDDEN)
	{
		if (GetTickCount() - timeRevival > FISH_MAN_REVIVAL_TIME)
		{
			SetState(FISH_MAN_STATE_HIDDEN);
			timeRevival = 0;
			SetPosition(posRevival);
			Simon::getInstance()->setIsInSpawn(false);
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (state != FISH_MAN_STATE_HIDDEN)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (int i = 0; i < (int)coEvents.size(); i++)
		{
			switch (coEvents[i]->obj->getID())
			{
			case ID_ENTITY_FLOOR:
				if (coEvents[i]->obj->getName().compare("HighFloor") == 0)
				{
					if (ny < 0)
					{
						vy = 0;
						Dy = min_ty * dy + ny * 0.1f;
						if (state == FISH_MAN_STATE_IDLE && timeWalk == 0)
						{
							timeWalk = GetTickCount();
							SetState(FISH_MAN_STATE_WALK);
						}
					}
				}
				else
				{
					if (ny != 0) vy = 0;
					Dy = min_ty * dy + ny * 0.1f;
				}
				break;
			}
		}
		x += Dx;
		y += Dy;
	}

	if (timeWalk && GetTickCount() - timeWalk > FISH_MAN_WALK)
	{
		timeWalk = 0;
		timeShoot = GetTickCount();
		SetState(FISH_MAN_STATE_SHOOT);
		CrystalBall* crystalBall = new CrystalBall(D3DXVECTOR2(x, y), nx);
		coObjects->push_back(crystalBall);
	}

	if (timeShoot && GetTickCount() - timeShoot > FISH_MAN_SHOOT)
	{
		timeShoot = 0;
		SetState(FISH_MAN_STATE_WALK);
		nx = -nx;
		timeWalk = GetTickCount();
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	Enemy::Update(dt, coObjects);
}

void FishMan::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 34;
	bottom = y + 66;
}

void FishMan::handleState()
{
	switch (state)
	{
	case FISH_MAN_STATE_IDLE:
		vx = 0;
		currentAnimation = FISH_MAN_ANI_IDLE;
		break;
	case FISH_MAN_STATE_WALK:
		vx = nx * FISH_MAN_SPEED_WALK;
		vy = 0;
		currentAnimation = FISH_MAN_ANI_WALK;
		break;
	case FISH_MAN_STATE_SHOOT:
		vx = 0;
		currentAnimation = FISH_MAN_ANI_SHOOT;
		break;
	case FISH_MAN_STATE_HIDDEN:
		vx = 0;
		break;
	}
}

FishMan::~FishMan()
{
}
