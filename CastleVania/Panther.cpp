#include "Panther.h"

constexpr float PANTHER_RUN_SPEED = 0.18f;
constexpr float PANTHER_GRAVITY = 0.0012f;
constexpr float PANTHER_JUMP_SPEED = 0.3f;

Panther::Panther(D3DXVECTOR2 position, int nx)
{
	id = ID_ENTITY_PANTHER;
	SetPosition(position);
	set_nx(1);
	isOnGround = true;
	state = PANTHER_STATE_IDLE;
	AddAnimation(PANTHER_ANI_IDLE);
	AddAnimation(PANTHER_ANI_MOVE);
	AddAnimation(PANTHER_ANI_JUMP);
	currentAnimation = PANTHER_ANI_IDLE;
	bbActivateLeft.left = bbActivateLeft.right = bbActivateLeft.top = bbActivateLeft.bottom = 0;
	bbActivateRight.left = bbActivateRight.right = bbActivateRight.top = bbActivateRight.bottom = 0;
}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	vector<LPGAMEOBJECT> floorObjects;

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getName().compare("WallActivatePanther") == 0)
		{
			if (coObjects->at(i)->getEnemyName().compare(this->name) == 0)	
			{
				if (coObjects->at(i)->get_nx() < 0 && bbActivateLeft.left == 0)
				{
					float l, t, r, b;
					coObjects->at(i)->GetBoundingBox(l, t, r, b);
					setBBActivateLeft(RECT{ long(l), long(t),long(r),long(b) });
				}
				else if (coObjects->at(i)->get_nx() > 0 && bbActivateRight.left == 0)
				{
					float l, t, r, b;
					coObjects->at(i)->GetBoundingBox(l, t, r, b);
					setBBActivateRight(RECT{ long(l), long(t),long(r),long(b) });
				}
			}
		}
		else if (coObjects->at(i)->getID()== ID_ENTITY_FLOOR )
		{
			floorObjects.push_back(coObjects->at(i));
		}
	}

	handleState();

	vy += PANTHER_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != STATE_DETROY)
		CalcPotentialCollisions(&floorObjects, coEvents);

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
		y += min_ty * dy + ny * 0.1f;

		if (ny < 0 )
		{
			vy = 0;
			floor = dynamic_cast<Floor*>(coEventsResult.back()->obj);
			if (!isOnGround && floor->getName().compare("Floor")==0)
			{
				vx = -vx;
				this->nx = -this->nx;
				isOnGround = true;
				state = PANTHER_STATE_ACTIVATE;
			}
		}
		else y += dy;
		x += dx;

		if (state == PANTHER_STATE_IDLE && activate)
		{
			state = PANTHER_STATE_ACTIVATE;
			vx = -this->nx * PANTHER_RUN_SPEED;
			isOnGround = false;
		}

		if (isOnGround && floor && state == PANTHER_STATE_ACTIVATE)
		{
			float fl, ft, fr, fb, pl, pt, pr, pb;
			floor->GetBoundingBox(fl, ft, fr, fb);
			GetBoundingBox(pl, pt, pr, pb);
			if ((pl < fl && fl - pl < 2) || (pr > fr && pr - fr < 2))
			{
				vy = -PANTHER_JUMP_SPEED;
				state = PANTHER_STATE_JUMP;
				isOnGround = false;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	Enemy::Update(dt, coObjects);
}

void Panther::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	if (state!= STATE_EFFECT)
	{
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;

		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);

		if (!checkInsideViewPort(viewport) && state == PANTHER_STATE_ACTIVATE)
		{
			state = STATE_DETROY;
		}
	}
	Enemy::Render(viewport);
}

void Panther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Panther::setBBActivateLeft(RECT bbActivateLeft)
{
	this->bbActivateLeft = bbActivateLeft;
}

void Panther::setBBActivateRight(RECT bbActivateRight)
{
	this->bbActivateRight = bbActivateRight;
}

void Panther::handleState()
{
	switch (state)
	{
	case PANTHER_STATE_IDLE:
		vx = 0;
		currentAnimation = PANTHER_ANI_IDLE;
		break;
	case PANTHER_STATE_JUMP:
		currentAnimation = PANTHER_ANI_JUMP;
		break;
	case PANTHER_STATE_ACTIVATE:
		currentAnimation = PANTHER_ANI_MOVE;
		break;
	}
}

Panther::~Panther()
{
}
