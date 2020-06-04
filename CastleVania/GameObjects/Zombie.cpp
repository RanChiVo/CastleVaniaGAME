#include "Zombie.h"

constexpr float ZOMBIE_WALKING_SPEED = 0.1f;
constexpr float ZOMBIE_GRAVITY = 0.001f;

Zombie::Zombie()
{
	id = ID_ENTITY_ZOMBIE;
	state = STATE_SHOW;
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_ZOMBIE);
	SetAnimationSet(ani_set);
	currentAnimation = ZOMBIE_ANI_WALKING;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
}

void Zombie::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case ZOMBIE_STATE_WALKING:
		vx = nx * ZOMBIE_WALKING_SPEED;
		currentAnimation = ZOMBIE_ANI_WALKING;
		break;
	}
}

bool Zombie::checkInsideViewPort(Viewport * viewport, D3DXVECTOR2 position)
{
	if ((position.x + width) < viewport->getX() ||
		position.x > (viewport->getX() + viewport->getWidth()))
	{
		return false;
	}
	return true;
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != STATE_EFFECT)
	{
		vy += ZOMBIE_GRAVITY * dt;

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
			// block 
			for (int i = 0; i < coEventsResult.size(); i++)
			{
				switch (coEventsResult[i]->obj->getID())
				{
				case ID_ENTITY_WALL:
					state = STATE_DETROY;
					break;
				}
			}
			x += dx;
			if (ny < 0)
			{
				vy = 0;
				y += min_ty * dy + ny * 0.4f;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	Enemy::Update(dt, coObjects);
}

void Zombie::Render(Viewport* viewport)
{
	if (state!= STATE_EFFECT)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == -1) flip = normal;
		else flip = flip_horiz;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	Enemy::Render(viewport);
}

Zombie::~Zombie()
{
}
