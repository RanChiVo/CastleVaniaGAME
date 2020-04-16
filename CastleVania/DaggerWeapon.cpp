#include "DaggerWeapon.h"

DaggerWeapon::DaggerWeapon()
{
	id = ID_ENTITY_DAGGER_WEAPON;
	state = STATE_SHOW;
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_DAGGER);
	SetAnimationSet(ani_set);
	currentAnimation = DAGGER_ANI;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_DAGGER).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_DAGGER).second;
}

void DaggerWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = nx * 0.18f;
	CombatWeapon::Update(dt, coObjects);
}

void DaggerWeapon::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	if (checkInsideViewPort(viewport))
	{
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else {
		state = STATE_DETROY;
	}
}

void DaggerWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

DaggerWeapon::~DaggerWeapon()
{
}
