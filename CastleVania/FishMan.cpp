#include "FishMan.h"
#include "ResourceManagement.h"
#include "./CrystalBall.h"
#include "./WaterEffect.h"

constexpr float FISH_MAN_GRAVITY = 0.001f;
constexpr float FISH_MAN_SPEED_WALK = 0.08f;
constexpr float FISH_MAN_SPEED_JUMP = 0.7f;
constexpr DWORD  FISH_MAN_SHOOT = 3000;
constexpr DWORD  FISH_MAN_WALK = 1200;
constexpr DWORD  FISH_MAN_REVIVAL_TIME = 20000;

FishMan::FishMan(D3DXVECTOR2 position)
{
	id = ID_ENTITY_FISH_MAN;
	AddAnimation(FISH_MAN_ANI_IDLE);
	AddAnimation(FISH_MAN_ANI_WALK);
	AddAnimation(FISH_MAN_ANI_SHOOT);
	currentAnimation = FISH_MAN_ANI_IDLE;
	state = FISH_MAN_STATE_HIDDEN;
	posRevival = position;
	vx = 0;
	timeRevival = 0;
	simon = Simon::getInstance();
}

void FishMan::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	//RenderBoundingBox(viewport);
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	if (!checkInsideViewPort(viewport))
	{
		SetState(FISH_MAN_STATE_HIDDEN);
	}

	if (state != STATE_EFFECT && state != FISH_MAN_STATE_HIDDEN)
	{
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	Enemy::Render(viewport);
}

void FishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	handleState();

	if (state == FISH_MAN_STATE_HIDDEN)
	{
		if (Simon::getInstance()->checkisInSpawn() && Simon::getInstance()->getIdEnemySpawn() == id)
		{
			if (isActivated)
			{
				if (GetTickCount() - timeRevival > 3000 && timeRevival > 0)
				{
					SetState(FISH_MAN_STATE_IDLE);
					timeRevival = 0;
					vy = -FISH_MAN_SPEED_JUMP;
					WaterEffect* effect = new WaterEffect(getPosition());
					coObjects->push_back(effect);
				}
			}
			else
			{
				isActivated = true;
				SetState(FISH_MAN_STATE_IDLE);
				vy = -FISH_MAN_SPEED_JUMP;
				WaterEffect* effect = new WaterEffect(getPosition());
				coObjects->push_back(effect);
			}
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (state != FISH_MAN_STATE_HIDDEN)
		CalcPotentialCollisions(coObjects, coEvents);

	if (state != FISH_MAN_STATE_HIDDEN)
	{
		vy += FISH_MAN_GRAVITY * dt;


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
					else if (coEvents[i]->obj->getName().compare("Floor") == 0)
					{
						SetState(FISH_MAN_STATE_HIDDEN);
						if (ny != 0) vy = 0;
						Dy = min_ty * dy + ny * 0.1f;
					}

					if (coEvents[i]->obj->getName().compare("Water") == 0)
					{
						WaterEffect* effect = new WaterEffect(getPosition());
						coObjects->push_back(effect);
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
			CrystalBall* crystalBall = new CrystalBall(D3DXVECTOR2(x + nx * 16, y), nx);
			coObjects->push_back(crystalBall);
		}

		if (timeShoot && GetTickCount() - timeShoot > FISH_MAN_SHOOT)
		{
			timeShoot = 0;
			SetState(FISH_MAN_STATE_WALK);
			nx = -nx;
			timeWalk = GetTickCount();
		}
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

void FishMan::setTimeRevival(DWORD timeRevival)
{
	this->timeRevival = timeRevival;
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
		currentAnimation = FISH_MAN_ANI_WALK;
		break;
	case FISH_MAN_STATE_SHOOT:
		vx = 0;
		currentAnimation = FISH_MAN_ANI_SHOOT;
		break;
	case FISH_MAN_STATE_HIDDEN:
		if (isActivated)
		{
			if (name.compare("FirstFishMan") == 0)
			{
				SetPosition(D3DXVECTOR2(Simon::getInstance()->getPosition().x - 64, posRevival.y));
			}
			else if (name.compare("SecondFishMan") == 0)
			{
				SetPosition(D3DXVECTOR2(Simon::getInstance()->getPosition().x + 64, posRevival.y));
			}
			if (timeRevival == 0)
			{
				setTimeRevival(GetTickCount());
			}
		}
		vy = 0;
		vx = 0;
		break;
	}
}

FishMan::~FishMan()
{
}
