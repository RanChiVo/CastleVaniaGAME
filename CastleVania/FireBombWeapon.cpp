#include "FireBombWeapon.h"
#include "ResourceManagement.h"

constexpr float FIRE_BOMP_SPEED_X = 0.18f;;
constexpr float FIRE_BOMP_GRAVITY = 0.0008f;
constexpr float FIRE_BOMP_THROW_SPEED_Y = 0.24f;
constexpr int FIRE_BOMP_FIRE_TIME = 4000;

FireBombWeapon::FireBombWeapon()
{
	fireStart = 0;
	id = ID_ENTITY_FIRE_BOMP_WEAPON;
	state = STATE_SHOW;
	vy = - FIRE_BOMP_THROW_SPEED_Y;
	vx = FIRE_BOMP_SPEED_X;
	AddAnimation(FIRE_BOMP_ANI1);
	AddAnimation(FIRE_BOMP_ANI2);
	AddAnimation(FIRE_BOMP_ANI3);
	AddAnimation(FIRE_BOMP_ANI4);
	AddAnimation(FIRE_BOMP_ANI5);
	currentAnimation = FIRE_BOMP_ANI1;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_FIRE_BOMB).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_FIRE_BOMB).second;
}

void FireBombWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (GetTickCount() - fireStart >= FIRE_BOMP_FIRE_TIME && fireStart > 0)
		SetState(STATE_DETROY);	

	if (!isOnGround)
	{
		vx = nx * FIRE_BOMP_SPEED_X;
		vy += FIRE_BOMP_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		vector<LPGAMEOBJECT> floorObjects;

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->getID() == ID_ENTITY_FLOOR)
			{
				floorObjects.push_back(coObjects->at(i));
			}
		}

		CalcPotentialCollisions(&floorObjects, coEvents);

		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			y += min_ty * dy + ny * 0.1f;

			if (ny != 0)
			{
				vx = 0;
				vy = 0;
				isOnGround = true;
				fireStart = GetTickCount();
			}
			x += dx;
			y += dy;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		coEvents.clear();
	}
	CombatWeapon::Update(dt, coObjects);
}

void FireBombWeapon::Render(Viewport * viewport)
{
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = normal;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
}

void FireBombWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

FireBombWeapon::~FireBombWeapon()
{
}
