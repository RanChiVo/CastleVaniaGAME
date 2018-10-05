#include "Simon.h"


Simon::Simon()
{
	initialize();
}

void Simon::initialize()
{
	loadResource();
}

void Simon::Update(DWORD dt)
{
	GameObject::Update(dt);

	// simple JUMP
	vy += SIMON_GRAVITY;
	if (y > 100)		
	{	
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 280) x = 280;
	if (vx < 0 && x < 0) x = 0;
}

void Simon::loadResource()
{

	AddAnimation(400);		// idle right
	AddAnimation(401);		// idle left
	AddAnimation(500);		// walk right
	AddAnimation(501);		// walk left

	SetPosition(0.0f, 100.0f);
}

void Simon::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx>0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;
	else ani = SIMON_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_MOVE_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		if (y == 100)
			vy = -SIMON_JUMP_SPEED_Y;

	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	}
}

Simon::~Simon()
{
}

