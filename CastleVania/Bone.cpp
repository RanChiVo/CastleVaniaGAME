#include "Bone.h"
#include "GameObjects/Simon.h"

constexpr float BONE_SPEED = 0.07f;
constexpr float BONE_GRAVITY = 0.0004f;
constexpr float BONE_THROW_SPEED = 0.3f;
constexpr int BONE_WIDTH = 32;
constexpr int BONE_HEIGHT = 32;

Bone::Bone()
{
	id = ID_ENTITY_AXE_WEAPON;
	state = STATE_SHOW;
	vy = -BONE_THROW_SPEED;
	vx = BONE_SPEED;
	nx = 1;
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_WHITE_SKELETON);
	SetAnimationSet(ani_set);
	currentAnimation = WHITE_SKELETON_THROW_BONE_ANI;
	width = BONE_WIDTH;
	height = BONE_HEIGHT;
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (startThrowNext > 0 && GetTickCount()- startThrowNext > 400)
	{
		isFinishNext = true;
		startThrowNext = 0;
	}

	if (startAttack > 0 && GetTickCount() - startAttack > 4000)
	{
		startAttack = 0;
		state = STATE_DETROY;
	}

	vx = nx * BONE_SPEED;
	vy += BONE_GRAVITY * dt;
	
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
	/*	x += min_tx * dx + nx * 0.4f;		
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/

		for (size_t i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult.at(i);
			static_cast<Simon*>(e->obj)->SetState(Simon::SIMON_STATE_HURT);
			isFinishNext = true;
		}
	}
	coEvents.clear();

}

void Bone::Render(Viewport * viewport)
{
	if (!checkInsideViewPort(viewport))
	{
		isFinishNext = true;
	}
	if (!isStart) return;
	if (isFinishNext) return;
	/*if (state == STATE_DETROY)
	{
		return;
	}*/
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	animation_set->at(currentAnimation)->Render(position.x, position.y, flip);
}

void Bone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Bone::StartThrow()
{
	if (startThrowNext==0)
	{
		startThrowNext = GetTickCount();
	}
}

void Bone::StartAttack()
{
	if (startAttack==0)
	{
		startAttack = GetTickCount();
	}
}

DWORD Bone::GetStartAttack()
{
	return startAttack;
}

Bone::~Bone()
{
}
