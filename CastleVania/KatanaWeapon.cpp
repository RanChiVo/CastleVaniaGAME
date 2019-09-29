#include "KatanaWeapon.h"
#include "ResourceManagement.h"
#include "../CastleVania/GameObjects/BurnBarrel.h"

constexpr int KATANAWEAPON_Y = 350;
constexpr int KATA_WIDTH = 30;
constexpr int KATA_HEIGHT = 20;

KatanaWeapon::KatanaWeapon()
{
	id = ID_TEX_KATANA_WEAPON;

	LPANIMATION ani;

	ani = new Animation(40);
	ani->Add("katana1");
	Animations::GetInstance()->Add(KATANAWEAPON_ANI, ani);

	AddAnimation(KATANAWEAPON_ANI);

	currentAnimation = KATANAWEAPON_ANI;

	this->width = KATA_WIDTH;
	this->height = KATA_HEIGHT;
}

void KatanaWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state != STATE_DETROY)
	{
		x += dx;
		y = KATANAWEAPON_Y;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		float min_tx, min_ty, nx, ny;
		float Dx = dx;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)

		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<BurnBarrel *>(e->obj))
			{
				BurnBarrel *burn_barrel = dynamic_cast<BurnBarrel *>(e->obj);
				if (e->nx != 0)
				{
					burn_barrel->SetState(STATE_DETROY);
				}
			}
		}
		x += Dx;

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void KatanaWeapon::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	if (checkInsideViewPort(viewport, D3DXVECTOR2(x, y)))
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else {
		state = STATE_DETROY;
	}
}

void KatanaWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

void KatanaWeapon::SetState(int state)
{
	switch (state)
	{
	case KATANAWEAPON_STATE_RIGHT:
		nx = 1;
		vx = KATANAWEAPON_SPEED_HIT;
		currentAnimation = KATANAWEAPON_ANI;
		break;
	case KATANAWEAPON_STATE_LEFT:
		nx = -1;
		vx = -KATANAWEAPON_SPEED_HIT;
		currentAnimation = KATANAWEAPON_ANI;
		break;
	}
}

bool KatanaWeapon::checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position)
{
	if ((position.x + width) < viewport->getX() || position.x >(viewport->getX() + viewport->getWidth()))
	{
		return false;
	}
	return true;
}

KatanaWeapon::~KatanaWeapon()
{
}
