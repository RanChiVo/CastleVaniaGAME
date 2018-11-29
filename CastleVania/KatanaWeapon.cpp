#include "KatanaWeapon.h"
#include "ResourceManagement.h"
#include "../CastleVania/GameObjects/BurnBarrel.h"

constexpr int KATANAWEAPON_Y = 309;

KatanaWeapon::KatanaWeapon(D3DXVECTOR2 position)
{
	id = ID_TEX_KATANA_WEAPON;

	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(40);
	ani->Add("katana1");
	Animations::GetInstance()->Add(KATANAWEAPON_ANI, ani);

	AddAnimation(KATANAWEAPON_ANI);

	currentAnimation = KATANAWEAPON_ANI;
}

void KatanaWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

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
					burn_barrel->SetPosition(D3DXVECTOR2(-100, -100));
				}
			}
		}
		x += Dx;

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void KatanaWeapon::Render(Viewport * viewport)
{
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	if (x < viewport->getX() || x >(viewport->getX() + viewport->getWidth()))
		return;
	
	else animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

void KatanaWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_KATANA)->Get("katana1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void KatanaWeapon::SetState(int state)
{
	GameObject::SetState(state);
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

KatanaWeapon::~KatanaWeapon()
{
}
