#include  "../Animations/Animations.h"
#include "../ResourceManagement.h"
#include "Katana.h"

constexpr float KATANA_GRAVITY = 0.0006f;

Katana::Katana()
{
}

Katana::Katana(D3DXVECTOR2 position)
{
	id = ID_TEX_KATANA;

	x = position.x;
	y = position.y;

	AddAnimation(KATANA_ANI);

	state = KATANA_STATE_HIDE;
	currentAnimation = KATANA_ANI;
}

void Katana::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);
	
	if (state == KATANA_STATE_SHOW)
	{

		vy += KATANA_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != KATANA_STATE_HIDE)
			CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
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
	else return;
}

void Katana::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_KATANA)->Get("katana1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void Katana::Render(Viewport * viewport)
{
	if (state == KATANA_STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else
	{
		return;
	}
}

Katana::~Katana()
{
}
