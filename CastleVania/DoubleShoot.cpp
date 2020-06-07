#include "DoubleShoot.h"

constexpr float DOUBLE_GRAVITY = 0.0006f;

DoubleShoot::DoubleShoot(D3DXVECTOR2 position)
{
	id = ID_ENTITY_DOUBLE_SHOOT;
	//AddAnimation(HEART_ANI);
	SetPosition(position);
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(id);
	SetAnimationSet(ani_set);
	currentAnimation = DOUBLE_SHOOT_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void DoubleShoot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == STATE_SHOW)
	{
		vy += DOUBLE_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			float Dx = dx, Dy = dy;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			for (int i = 0; i < coEvents.size(); i++)
			{
				switch (coEvents[i]->obj->getID())
				{
				case ID_ENTITY_FLOOR:
					if (ny < 0) vy = 0;
					Dy = min_ty * dy + ny * 0.08f;
					break;
				}
			}
			y += Dy;
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (GetTickCount() - liveTime > 4000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
	}
}

void DoubleShoot::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void DoubleShoot::Render(Viewport * viewport)
{
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = normal;

		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);

		RenderBoundingBox(viewport);
	}
}

DoubleShoot::~DoubleShoot()
{
}
