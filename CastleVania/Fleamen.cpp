#include "Fleamen.h"
#include "GameObjects/Floor.h"
#include  "GameObjects/Simon.h"

constexpr float FLEAMEN_SPEED_X = 0.15f;
constexpr float FLEAMEN_SPEED_Y = 0.05f;
constexpr float FLEAMEN_GRAVITY = 0.0009f;

Fleamen::Fleamen(D3DXVECTOR2 pos, int width, int height)
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
		y += min_ty * dy + ny * 0.008f;

		if (ny < 0)
		{
			if (!isOnGround)
			{
				isOnGround = true;
			}
			Floor* floor = dynamic_cast<Floor*>(coEventsResult.back()->obj);
			vy = 0;
			if (floor && isActivate)
			{
				SetState(FLEAMEN_STATE_IDLE);
			}
		}
		else y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (state == FLEAMEN_STATE_IDLE)
	{
		if ( timeJumpToPlayer == 0 && x > Simon::getInstance()->getPosition().x )
		{
			timeJumpToPlayer = GetTickCount();
			nx = 1;
			vx = 0.18f;
			SetState(FLEAMEN_STATE_JUMP_ATTACK);
		}
		else if (timeJumpToPlayer==0 && timeJumpToPlayer == 0 && x < Simon::getInstance()->getPosition().x)
		{
			nx = -1;
			SetState(FLEAMEN_STATE_JUMP_ON_FLOOR);
			vx =- 0.18f;
			timeJumpToPlayer = GetTickCount();
		}
	}

	if (timeJumpToPlayer > 0 && GetTickCount() - timeJumpToPlayer == 3000)
	{
		timeJumpToPlayer = 0;
		SetState(FLEAMEN_STATE_JUMP_ATTACK);
	}
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
	if (state == FLEAMEN_STATE_JUMP_ATTACK)
	{
		if (vy >= 0)
		{
			currentAnimation == FLEAMEN_ANI_IDLE;
		}
	}
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	RenderBoundingBox(viewport);
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
	Enemy::Render(viewport);
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
		vy = -0.21f;
		y -= 20;
		vx = nx * 0.18f;
		isOnGround = false;
		isJumping = true;
		currentAnimation = FLEAMEN_ANI_JUMP_ATTACK;
	}
	break;
	case FLEAMEN_STATE_JUMP_ON_FLOOR:
	{
		vy = -0.21f;
		y -= 5;
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
	isActivate = true;
	SetState(FLEAMEN_STATE_JUMP_ATTACK);
}

Fleamen::~Fleamen()
{
}
