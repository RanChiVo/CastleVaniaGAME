#include "Skeleton.h"
#include "GameObjects/Floor.h"
#include "GameObjects/Simon.h"
#include "Wall.h"
#include "Brick.h"

constexpr float SKELETON_GRAVITY = 0.0015f;
constexpr float SKELETON_SPEED_Y = 0.3f;
constexpr float SKELETON_SPEED_X = 0.15f;

Skeleton::Skeleton(D3DXVECTOR2 pos, int nx, int height, int width)
{
	id = ID_ENTITY_WHITE_SKELETON;
	SetPosition(pos);
	XOrginal = pos.x;
	YOrginal = pos.y;
	distanceMoving = 40;
	this->height = height;
	this->width = width;
	this->nx = 1;
	vx = 0;
	vy = 0;
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float sx = Simon::getInstance()->getPosition().x;

	vy += SKELETON_GRAVITY * dt;
	
	if (isActive && !isActiveFirst)
	{
		SetState(SKELETON_STATE_ACTIVE);
		isActiveFirst = true;
	}

	if (isActiveFirst)
	{
		bool go_out_distane = false;
		if (abs(sx - x) < 85)
		{
			if ((nx == 1 && sx > x) ||
				(nx == -1 && sx < x))
			{
				if (!isJumping)
				{
					XOrginal = x;
					nx = -nx;
				}
				go_out_distane = true;
				if (sx > x)
				{
					XorginalSimon = sx - 85;
				}
				else {
					XorginalSimon = sx + 85;
				}
			}
		}

		if (!isJumping&& go_out_distane)
		{
			if (XorginalSimon < sx)
			{
				XorginalSimon = sx;
				nx = (sx > x) ? 1 : -1;
			}
			else if (XorginalSimon > sx)
			{
				XorginalSimon = sx;
				nx = (sx > x) ? -1 : 1;
			}
		}

		if (abs(XOrginal - x) > distanceMoving)
		{
			if ((nx == 1 && sx > x) || (nx == -1 && sx < x))
			{
				distanceMoving = 40 + abs(abs(sx - x) - 85);
			}
			else
			{
				if (!isJumping)
				{
					XOrginal = x;
					nx = -nx;
				}
			}
		}
	}
	Enemy::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> staticObject;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_FLOOR ||
			coObjects->at(i)->getID() == ID_ENTITY_BRICK
			&& coObjects->at(i)->getName().compare("EdgeBrick") == 0)
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

		if (nx == 0)
		{
			x += dx;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Floor*>(e->obj))
			{
				Floor* floor = dynamic_cast<Floor*>(e->obj);
				if (e->ny < 0)
				{
					vy = 0;
					Dy = min_ty * dy + ny * 0.11f;
					if (!isOnGround)
					{
						isOnGround = true;
					}
					SetState(SKELETON_STATE_IDLE);
					isJumping = false;
					vx = 0;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				CBrick* edge = dynamic_cast<CBrick*>(e->obj);
				if (isActiveFirst)
				{
					if (sx < XGoOutActivateArea)
					{
						if ((abs(sx - x) < 85 ) && y <= (YOrginal+5))
						{
							if (e->nx != 0)
							{
								if (!isJumping)
								{
									this->nx = -this->nx;
								}
							}
						}
						
						if (e->nx != 0 || e->ny != 0)
						{
							if ((abs(sx - x) <= 50))
							{
								if (edge && isActiveFirst && edge->get_nx() >= 0)
								{
									SetState(SKELETON_STATE_JUMP_RIGHT);
								}
								if (edge &&isActiveFirst&& edge->get_nx() < 0)
								{
									SetState(SKELETON_STATE_JUMP_LEFT);
								}
							}
							else
							{
								if (edge && isActiveFirst && edge->get_nx() > 0)
								{
									SetState(SKELETON_STATE_JUMP_RIGHT);
								}
								if (edge &&isActiveFirst&& edge->get_nx() < 0)
								{
									SetState(SKELETON_STATE_JUMP_LEFT);
								}
							}
						}
					}
					else
					{
						if (e->nx != 0 || e->ny != 0)
						{
							if (edge && isActiveFirst )
							{
								SetState(SKELETON_STATE_JUMP_RIGHT);
							}
						}
					}
				}
			}
		}
		y += Dy;
	}
	coEvents.clear();
	if (!isJumping)
	{
		vx = nx * 0.1f;
	}

	/*if (isActiveFirst ==true && startmoving == 0 && timeActivate > 0
		&& (GetTickCount() - timeActivate > 2000))
	{
		SetState(SKELETON_STATE_WALKING);
		Reset();
	}

	if (state==SKELETON_STATE_WALKING && startmoving > 0)
	{
		timemoving += RandomTime(-5, 10);
	}

	if (state== SKELETON_STATE_WALKING && startmoving  > 0
		&& GetTickCount()- startmoving > timemoving)
	{
		Reset();
	}*/
}

void Skeleton::Reset()
{
	startmoving = GetTickCount();
	timemoving = RandomTime(500, 700);
	if (vx > 0)
	{
		vx = -0.05f;
	}
	else vx = 0.05f;
}

DWORD Skeleton::RandomTime(DWORD time1, DWORD time2)
{
	DWORD time[2] = { time1, time2 };
	int t = rand() % 2;
	return time[t];
}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Skeleton::Render(Viewport * viewport)
{
	if (!isActive)
	{
		return;
	}
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (x < Simon::getInstance()->getPosition().x)
	{
		nx_Render = 1;
	}
	else nx_Render = -1;
	if (nx_Render == -1) flip = normal;
	else flip = flip_horiz;
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
}

void Skeleton::SetActivate(bool isActive)
{
	if (!this->isActive)
	{
		this->isActive = isActive;
	}
}

void Skeleton::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case SKELETON_STATE_ACTIVE:
		currentAnimation = WHITE_SKELETON_ATTACK;
		Simon::getInstance()->get_nx();
		vx = 0;
		//vx = 0.05f;
		//vy = -SKELETON_SPEED_Y * 2;
		//y -= 5;
		break;
	case SKELETON_STATE_IDLE:
		vx = 0;
		break;
	case SKELETON_STATE_WALKING:
		currentAnimation = WHITE_SKELETON_ATTACK;
		Simon::getInstance()->get_nx();
		vx = 0.05f;
		vy = 0;
		break;
	case SKELETON_STATE_JUMP_LEFT:
		currentAnimation = WHITE_SKELETON_ATTACK;
		isJumping = true;
		vx =- 0.15f;
		vy = -SKELETON_SPEED_Y * 2;
		y -= 5;
		break;
	case SKELETON_STATE_JUMP_RIGHT:
		isJumping = true;
		currentAnimation = WHITE_SKELETON_ATTACK;
		vy = -SKELETON_SPEED_Y * 2;
		vx = 0.1f;
		y -= 5;
		break;
	}
}

Skeleton::~Skeleton()
{

}
