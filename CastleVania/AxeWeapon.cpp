#include "AxeWeapon.h"
#include "../CastleVania/ResourceManagement.h"

constexpr float AXE_SPEED = 0.35f;
constexpr float AXE_GRAVITY = 0.0015f;
constexpr float AXE_THROW_SPEED = 0.4f;

AxeWeapon::AxeWeapon()
{
	id = ID_ENTITY_AXE_WEAPON;
	state = STATE_SHOW;
	vy = -AXE_THROW_SPEED;
	vx = AXE_SPEED;
	AddAnimation(AXE_ANI);
	currentAnimation = AXE_ANI;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_AXE).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_AXE).second;
}

void AxeWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = nx*AXE_SPEED;
	vy += AXE_GRAVITY * dt;
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
		state = STATE_DETROY;
	}
}

void AxeWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

AxeWeapon::~AxeWeapon()
{
}
