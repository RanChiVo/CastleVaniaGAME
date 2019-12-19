#include "FireBombWeapon.h"
#include "ResourceManagement.h"

constexpr float FIRE_BOMP_SPEED_X = 0.1f;;
constexpr float FIRE_BOMP_GRAVITY = 0.0005f;
constexpr float FIRE_BOMP_THROW_SPEED_Y = 0.2f;
constexpr DWORD FIRE_BOMP_FIRE_TIME = 2000;

FireBombWeapon::FireBombWeapon()
{
	fireStart = 0;
	id = ID_ENTITY_FIRE_BOMP_WEAPON;
	state = STATE_SHOW;
	vy = - FIRE_BOMP_THROW_SPEED_Y;
	vx = FIRE_BOMP_SPEED_X;
	AddAnimation(FIRE_BOMP_ANI1);
	AddAnimation(FIRE_BOMP_ANI2);
	currentAnimation = FIRE_BOMP_ANI1;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_FIRE_BOMB).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_FIRE_BOMB).second;
}

void FireBombWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	handleState();

	if (state==STATE_SHOW)
	{
		vx = nx * FIRE_BOMP_SPEED_X;
		vy += FIRE_BOMP_GRAVITY * dt;

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
						state = STATE_EFFECT;
						fireStart = GetTickCount();
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

	if (GetTickCount() - fireStart > FIRE_BOMP_FIRE_TIME && fireStart > 0)
		SetState(STATE_DETROY);
}

void FireBombWeapon::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip = normal;
	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

void FireBombWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void FireBombWeapon::handleState()
{
	switch (state)
	{
	case STATE_SHOW:
		currentAnimation = FIRE_BOMP_ANI1;
		break;
	case STATE_EFFECT:
		currentAnimation = FIRE_BOMP_ANI2;
		break;
	}
}

FireBombWeapon::~FireBombWeapon()
{
}
