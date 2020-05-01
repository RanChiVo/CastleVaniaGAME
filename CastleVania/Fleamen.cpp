#include "Fleamen.h"
#include "GameObjects/Floor.h"
#include  "GameObjects/Simon.h"

constexpr float FLEAMEN_SPEED_X = 0.2f;
constexpr float FLEAMEN_SPEED_HIGHT_Y = 0.25f;
constexpr float FLEAMEN_SPEED_LOW_Y = 0.1f;
constexpr float FLEAMEN_GRAVITY = 0.0015f;

Fleamen::Fleamen(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_FLEAMEN;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	SetState(FLEAMEN_STATE_PREPAIR_ATTACK);
}

void Fleamen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	vy += FLEAMEN_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> staticObject;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_FLOOR ||
			coObjects->at(i)->getID() == ID_ENTITY_WALL)
			staticObject.push_back(coObjects->at(i));
	}

	CalcPotentialCollisions(&staticObject, coEvents);

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
		y += min_ty * dy + ny * 0.11f;
		if (ny < 0)
		{
			if (!isOnGround)
			{
				isOnGround = true;
			}
			Floor* floor = dynamic_cast<Floor*>(coEventsResult.back()->obj);
			vy = 0;
			if (floor && isActive)
			{
				SetState(FLEAMEN_STATE_IDLE);
			}
		}
		else y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (timeFirstJump > 0 && GetTickCount() - timeFirstJump >= 600)
	{
		timeFirstJump = 0;
		timeLowJump = GetTickCount();
		nx = Simon::getInstance()->get_nx();
	}
	HandleActivateTolLowJump();
	HandleLowTolHeightJump();
	HandleHeightToLowJump();
}

void Fleamen::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Fleamen::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	if (state == FLEAMEN_STATE_JUMP_ATTACK)
	{
		if (vy >= 0)
		{
			currentAnimation = FLEAMEN_ANI_IDLE;
		}
	}

	if (state == FLEAMEN_STATE_JUMP_ON_FLOOR)
	{
		if (vy >= 0)
		{
			currentAnimation = FLEAMEN_ANI_IDLE;
		}
	}
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	if (isActive && !checkInsideViewPort(viewport))
	{
		SetState(STATE_DETROY);
	}
}

void Fleamen::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case FLEAMEN_STATE_PREPAIR_ATTACK:
	{
		currentAnimation = FLEAMEN_ANI_PREPAIR_ATTACK;
	} 
	break;
	case FLEAMEN_STATE_JUMP_ATTACK:
	{
		vy = -FLEAMEN_SPEED_HIGHT_Y;
		y-= 5;
		vx = FLEAMEN_SPEED_X;
		isOnGround = false;
		isJumping = true;
		currentAnimation = FLEAMEN_ANI_JUMP_ATTACK;
	}
	break;
	case FLEAMEN_STATE_JUMP_ON_FLOOR:
	{
		vy = -FLEAMEN_SPEED_LOW_Y;
		isOnGround = false;
		isJumping = true;
		currentAnimation = FLEAMEN_ANI_JUMP_ATTACK;
	}
	break;
	case FLEAMEN_STATE_IDLE:
	{
		currentAnimation = FLEAMEN_ANI_IDLE;
		vx = 0;
		vy = 0;
	}
	break;
	}
}

void Fleamen::StartActivate()
{
	SetState(FLEAMEN_STATE_JUMP_ATTACK);
	vy = -FLEAMEN_SPEED_LOW_Y;
	y -= 10;
	isActive = true;
	timeFirstJump = GetTickCount();
}

void Fleamen::HandleActivateTolLowJump()
{
	
	if (timeLowJump && timeOnGround == 0)
	{
		SetState(FLEAMEN_STATE_JUMP_ON_FLOOR);
		if (x < Simon::getInstance()->getPosition().x )
		{
			nx = 1;
			vx = FLEAMEN_SPEED_X;
		}
		else if (x >= Simon::getInstance()->getPosition().x)
		{
			nx = -1;
			vx = -FLEAMEN_SPEED_X;
		}
		timeOnGround = GetTickCount();
	}

	if (timeLowJump && timeOnGround > 0 && GetTickCount() - timeOnGround >= 400)
	{
		timeOnGround = 0;
		hasLowJumpedDone = true;
	}
}

void Fleamen::HandleLowTolHeightJump()
{
	if (hasLowJumpedDone)
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);

		float ls, ts, rs, bs;
		Simon::getInstance()->GetBoundingBox(ls, ts, rs, bs);

		if (checkCollision(RECT{ long(l), long(t), long(r), long(b) }, RECT{ long(ls), long(ts), long(rs), long(bs) }))
		{
			timeLowJump = 0;
			timeJumpToPlayer = GetTickCount();
			SetState(FLEAMEN_STATE_JUMP_ATTACK);
			vx = nx * FLEAMEN_SPEED_X;
		}
	}
}

void Fleamen::HandleHeightToLowJump()
{
	if (timeJumpToPlayer > 0 && GetTickCount() - timeJumpToPlayer >= 600)
	{
		timeJumpToPlayer = 0;
		timeLowJump = GetTickCount();
		hasLowJumpedDone = false;
	}
}

Fleamen::~Fleamen()
{
}
