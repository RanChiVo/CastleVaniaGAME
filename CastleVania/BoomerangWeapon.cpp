#include "BoomerangWeapon.h"
#include "GameObjects/Simon.h"

constexpr float BOOMERANG_THROW_SPEED = 0.24f;
constexpr float BOOMERANG_THROW_TIME = 1000;

BoomerangWeapon::BoomerangWeapon()
{
	id = ID_ENTITY_BOOMERANG_WEAPON;
	//AddAnimation(BOOMERANG_WEAPON_ANI);
	currentAnimation = BOOMERANG_WEAPON_ANI;
	state = STATE_SHOW;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_BOOMERANG).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_BOOMERANG).second;
	liveTime = 0;
}

void BoomerangWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = nx * BOOMERANG_THROW_SPEED;
	if (liveTime > 0 && GetTickCount() - liveTime > BOOMERANG_THROW_TIME )
	{
		vx = -vx;
		nx = -nx;
		liveTime = 0;
		goBack = true;
	}
	if (goBack)
	{
		float left1, top1, right1, bottom1;
		Simon::getInstance()->GetBoundingBox(left1, top1, right1, bottom1);
		RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };
		float left2, top2, right2, bottom2;
		GetBoundingBox(left2, top2, right2, bottom2);
		RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };
		bool result = this->checkCollision(rect1, rect2);
		if (result)
		{
			SetState(STATE_DETROY);
		}
	}
	CombatWeapon::Update(dt, coObjects);
}

void BoomerangWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void BoomerangWeapon::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	if (checkInsideViewPort(viewport))
	{
		animation_set->at(currentAnimation)->Render(position.x, position.y, flip);
	}
	else {
		state = STATE_DETROY;
	}
}

BoomerangWeapon::~BoomerangWeapon()
{
}
