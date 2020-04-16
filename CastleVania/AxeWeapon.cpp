#include "AxeWeapon.h"

constexpr float AXE_SPEED = 0.18f;
constexpr float AXE_GRAVITY = 0.0004f;
constexpr float AXE_THROW_SPEED = 0.2f;

AxeWeapon::AxeWeapon()
{
	id = ID_ENTITY_AXE_WEAPON;
	state = STATE_SHOW;
	vy = -AXE_THROW_SPEED;
	vx = AXE_SPEED;
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_AXE);
	SetAnimationSet(ani_set);
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
		y += dy;
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
		animation_set->at(currentAnimation)->Render(position.x, position.y, flip);
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
