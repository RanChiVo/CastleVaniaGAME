#include "SpearKnight.h"
#include "GameObjects/Floor.h"
#include "GameObjects/Simon.h"

constexpr float SPEAR_KNIGHT_MIN_DISTANCE = 32;
constexpr float SPEAR_KNIGHT_GRAVITY = 0.0009f;
constexpr float SPEAR_KNIGHT_SPEED_X = 0.06f;


SpearKnight::SpearKnight(D3DXVECTOR2 pos, int maxDistance, int height, int width )
{
	id = ID_ENTITY_SPEAR_KNIGHT;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->maxDistance = maxDistance;
	currentAnimation = SPEAR_KNIGHT_ANI_WALKING;
	nx = 1;
	vx = SPEAR_KNIGHT_SPEED_X;
	positionXStart = pos.x;
}

void SpearKnight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (state!= STATE_EFFECT)
	{
		vy += SPEAR_KNIGHT_GRAVITY * dt;
		vx = nx * SPEAR_KNIGHT_SPEED_X;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();

		vector<LPGAMEOBJECT> staticObject;
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->getID() == ID_ENTITY_FLOOR)
				staticObject.push_back(coObjects->at(i));
		}

		CalcPotentialCollisions(&staticObject, coEvents);

		float min_tx, min_ty, _nx, ny;
		float Dx = dx, Dy = dy;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, _nx, ny, rdx, rdy);
		y += min_ty * dy + ny * 0.11f;
		if (ny != 0) vy = 0;
		for (int i = 0; i < (int)coEventsResult.size(); i++)
		{
			if (coEventsResult[i]->obj->getID() == ID_ENTITY_FLOOR)
			{
				highFloor = dynamic_cast<Floor *>(coEvents[i]->obj);
			}
		}

		if (highFloor && highFloor == Simon::getInstance()->GetHightFloor())
		{
			float averageDistance = (float)highFloor->getWidth() / 2;
			if (x < (maxDistance - 10) && x > (positionXStart + 10))
			{
				if (Simon::getInstance()->getPosition().x >= (positionXStart + averageDistance))
				{
					nx = 1;
				}
				else if (Simon::getInstance()->getPosition().x >= (positionXStart + averageDistance))
				{
					nx = -1;
				}
			}
		}

		if (x > maxDistance)
		{
			nx = -1;
			vx = -SPEAR_KNIGHT_SPEED_X;
		}
		else if (x < positionXStart)
		{
			nx = 1;
			vx = SPEAR_KNIGHT_SPEED_X;
		}
		x += dx;
	}
}

void SpearKnight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void SpearKnight::Render(Viewport * viewport)
{
	if (state != STATE_EFFECT)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	Enemy::Render(viewport);
}

SpearKnight::~SpearKnight()
{
}
