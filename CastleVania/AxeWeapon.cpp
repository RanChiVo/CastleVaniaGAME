#include "AxeWeapon.h"
#include "../CastleVania/ResourceManagement.h"

constexpr float AXE_SPEED = 0.2f;
constexpr float AXE_GRAVITY = 0.001f;
constexpr float AXE_THROW_SPEED = 0.4f;
constexpr DWORD AXE_FIRE_TIME = 2000;

AxeWeapon::AxeWeapon()
{
	id = ID_ENTITY_AXE_WEAPON;
	state = STATE_SHOW;
	vy = -AXE_THROW_SPEED;
	vx = AXE_SPEED;
	AddAnimation(AXE_ANI_THROW);
	currentAnimation = AXE_ANI_THROW;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_AXE).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_AXE).second;
}

void AxeWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == STATE_SHOW)
	{
		vx = nx * AXE_SPEED;
		vy += AXE_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx, ny;
			float Dx = dx, Dy = dy;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (int i = 0; i < coEvents.size(); i++)
			{
				switch (coEvents[i]->obj->getID())
				{
				case ID_ENTITY_FLOOR:
					if (ny != 0)
					{
						vx = 0;
						vy = 0;
						SetState(STATE_DETROY);
					}
					Dy = min_ty * dy + ny * 0.11f;
					break;
				}
			}
			y += Dy;
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	CombatWeapon::Update(dt, coObjects);
}

void AxeWeapon::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	
	if (checkInsideViewPort(viewport))
	{
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else {
		vy = -AXE_THROW_SPEED;
		vx = AXE_SPEED;
	}
}

void AxeWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

AxeWeapon::~AxeWeapon()
{
}
