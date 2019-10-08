#include "DaggerWeapon.h"
#include "ResourceManagement.h"
#include "../CastleVania/GameObjects/BurnBarrel.h"

constexpr int KATANAWEAPON_Y = 350;
constexpr int KATA_WIDTH = 30;
constexpr int KATA_HEIGHT = 20;

DaggerWeapon::DaggerWeapon()
{
	id = ID_TEX_KATANA_WEAPON;
	state = STATE_SHOW;
	LPANIMATION ani;

	ani = new Animation(40);
	ani->Add("katana1");
	Animations::GetInstance()->Add(KATANAWEAPON_ANI, ani);

	AddAnimation(KATANAWEAPON_ANI);

	currentAnimation = KATANAWEAPON_ANI;

	this->width = KATA_WIDTH;
	this->height = KATA_HEIGHT;
	y = KATANAWEAPON_Y;
}

void DaggerWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = nx * 0.18f;
	CombatWeapon::Update(dt, coObjects);
}

void DaggerWeapon::Render(Viewport * viewport)
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

void DaggerWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

void DaggerWeapon::SetState(int state)
{
	switch (state)
	{
	case KATANAWEAPON_STATE_RIGHT:
		nx = 1;
		currentAnimation = KATANAWEAPON_ANI;
		break;
	case KATANAWEAPON_STATE_LEFT:
		nx = -1;
		currentAnimation = KATANAWEAPON_ANI;
		break;
	}
}

bool DaggerWeapon::checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position)
{
	if ((position.x + width) < viewport->getX() || position.x >(viewport->getX() + viewport->getWidth()))
	{
		return false;
	}
	return true;
}

DaggerWeapon::~DaggerWeapon()
{
}
