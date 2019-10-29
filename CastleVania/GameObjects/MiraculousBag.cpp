#include "MiraculousBag.h"
#include "../ResourceManagement.h"

constexpr float MIRACULOUSBAG_GRAVITY = 0.0006f;

MiraculousBag::MiraculousBag(EntityID id)
{
	state = STATE_SHOW;
	AddAnimation(RED_MIRACULOUSBAG_ANI);
	AddAnimation(BLUE_MIRACULOUSBAG_ANI);
	AddAnimation(WHITE_MIRACULOUSBAG_ANI);
	AddAnimation(BONUS_MIRACULOUSBAG_ANI);
	switch (ID_ENTITY_RED_100_MIRACULOUS_BAG)
	{
	case ID_ENTITY_RED_100_MIRACULOUS_BAG:
		id = ID_ENTITY_RED_100_MIRACULOUS_BAG;
		currentAnimation = RED_MIRACULOUSBAG_ANI;
		break;
	case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
		id = ID_ENTITY_RED_100_MIRACULOUS_BAG;
		currentAnimation = BLUE_MIRACULOUSBAG_ANI;
		break;
	case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
		id = ID_ENTITY_WHITE_700_MIRACULOUS_BAG;
		currentAnimation = WHITE_MIRACULOUSBAG_ANI;
		break;
	case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
		id = ID_ENTITY_BONUS_1000_MIRACULOUS_BAG;
		currentAnimation = BONUS_MIRACULOUSBAG_ANI;
		break;
	}
}

void MiraculousBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == STATE_SHOW)
	{
		vy += MIRACULOUSBAG_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			y += min_ty * dy + ny * 0.4f;
			if (ny != 0) vy = 0;
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void MiraculousBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void MiraculousBag::Render(Viewport * viewport)
{
	if (state == STATE_SHOW)
	{
		animations.find(currentAnimation)->second->SetLoop(true);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
}

MiraculousBag::~MiraculousBag()
{
}
