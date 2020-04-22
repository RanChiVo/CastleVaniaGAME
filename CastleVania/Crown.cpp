#include "Crown.h"

constexpr float CROWN_GRAVITY = 0.0006f;

Crown::Crown(D3DXVECTOR2 position, int height, int width)
{
	id = ID_ENTITY_CROWN;
	SetPosition(position);
	currentAnimation = CROWN_ANI;
	this->width = width;
	this->height = height;
	state = STATE_HIDDEN;
	score = 2000;
}

void Crown::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;

	if (state == STATE_EFFECT)
	{
		if (timeEffect > 0 && GetTickCount() - timeEffect > 1000)
		{
			state = STATE_DETROY;
			timeEffect = 0;
		}
	}
	else if (state == STATE_SHOW && isActivate)
	{
		vy = -0.018f;
		isActivate = false;
		
	}
	else if (state == STATE_SHOW && !isActivate && liveTime > 0 && (GetTickCount() - liveTime > 2000))
	{
		vy = 0;
		liveTime = 0;
	}
}

void Crown::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + width;
	top = y;
	right = left + width;
	bottom = y + height;
}

void Crown::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;

	if (state == STATE_EFFECT)
	{
		AnimationSets * animation_sets = AnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_EFFECT_MONEY);
		SetAnimationSet(ani_set);
		currentAnimation = EFFECT_2000_MONEY_ANI;
		animation_set->find(currentAnimation)->second->Render(position.x + 30, position.y - 20, flip);
	}

	if (state == STATE_SHOW)
	{
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
}

void Crown::startAction()
{
	state = STATE_SHOW;
	liveTime = GetTickCount();
	isActivate = true;
}

int Crown::getScore()
{
	return score;
}

void Crown::setTimeEffect(DWORD time)
{
	timeEffect = time;
}


Crown::~Crown()
{
}
