#include "Skeleton.h"
#include "GameObjects/Floor.h"
#include "GameObjects/Simon.h"
#include "Wall.h"
#include "Brick.h"

constexpr float SKELETON_GRAVITY = 0.0015f;
constexpr float SKELETON_SPEED_Y = 0.3f;
constexpr float SKELETON_SPEED_X = 0.15f;

Skeleton::Skeleton(D3DXVECTOR2 pos, int nx,int height, int width)
{
	id = ID_ENTITY_WHITE_SKELETON;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->nx = nx;
	vx = 0;
	vy = 0;
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	vy += SKELETON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> staticObject;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_FLOOR|| 
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

		CBrick* edge = dynamic_cast<CBrick*>(coEventsResult.back()->obj);
		Floor* floor = dynamic_cast<Floor*>(coEventsResult.back()->obj);
		
		if (nx!=0)
		{
			float distanceSimon = x - Simon::getInstance()->getPosition().x;

			if (abs(distanceSimon) <= 50)
			{
				/*if (edge && edge->get_nx() < 0)
				{
					SetState(SKELETON_STATE_JUMP_LEFT);
					SetSpeed(0, 0);
				}
				else if (edge && edge->get_nx() > 0)
				{
					SetState(SKELETON_STATE_JUMP_RIGHT);
					SetSpeed(-vx, 0);
				}*/
			}
			else if (abs(distanceSimon) > 50)
			{
				if (edge && edge->get_nx() < 0)
				{
					SetState(SKELETON_STATE_JUMP_LEFT);
				}
				else if (edge && edge->get_nx() > 0)
				{
					SetState(SKELETON_STATE_JUMP_RIGHT);
				}
			}
		}
		else x += dx;

		if (ny < 0 && floor)
		{
			vy = 0;
			y += min_ty * dy + ny * 0.11f;
			if (!isOnGround)
			{
				isOnGround = true;
			}
		}
		else y += dy;
	}
	coEvents.clear();

	if (state!=SKELETON_STATE_ACTIVE && isActive && startmoving == 0)
	{
		SetState(SKELETON_STATE_WALKING);
	}

	if (state== SKELETON_STATE_WALKING && startmoving  > 0 
		&& GetTickCount()- startmoving > timemoving)
	{
		Reset();
	}
}

DWORD RandomTime(DWORD time1, DWORD time2)
{
	DWORD time[2] = { time1, time2 };
	int t = rand() % 2;
	return time[t];
}
void Skeleton::Reset()
{
	startmoving = GetTickCount();
	timemoving = RandomTime(1500, 2000);
	if (vx > 0)
	{
		vx = -0.15f;
	}
	else vx = 0.15f;
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
	if (nx == -1) flip = normal;
	else flip = flip_horiz;
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
}

void Skeleton::SetActivate(bool isActive)
{
	 this->isActive = isActive; 
	 SetState(SKELETON_STATE_ACTIVE);
}

void Skeleton::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case SKELETON_STATE_ACTIVE:
		currentAnimation = WHITE_SKELETON_ATTACK;
		Simon::getInstance()->get_nx();
		vx = 0.05f;
		vy = -SKELETON_SPEED_Y * 2;
		y -= 5;
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
		vx = -0.15 ;
		vy = -SKELETON_SPEED_Y;
		y -= 5;
		startmoving = 0;
		break;
	case SKELETON_STATE_JUMP_RIGHT:
		currentAnimation = WHITE_SKELETON_ATTACK;
		vx = 0.2;
		vy = -SKELETON_SPEED_Y * 1.25;
		y -= 5;
		startmoving = 0;
		break;
	}
}

Skeleton::~Skeleton()
{

}
