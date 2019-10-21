#include "DaggerWeapon.h"
#include "ResourceManagement.h"
#include "../CastleVania/GameObjects/BurnBarrel.h"

constexpr int DAGGER_WEAPON_Y = 350;
constexpr int DAGGER_WIDTH = 30;
constexpr int DAGGER_HEIGHT = 20;
constexpr int DAGGER_WEAPON_ANI = 32;
constexpr float DAGGER_WEAPON_SPEED_HIT = 0.6f;

DaggerWeapon::DaggerWeapon()
{
	id = ID_ENTITY_DAGGER_WEAPON;
	state = STATE_SHOW;
	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add("dagger");
	Animations::GetInstance()->Add(DAGGER_WEAPON_ANI, ani);

	AddAnimation(DAGGER_WEAPON_ANI);

	currentAnimation = DAGGER_WEAPON_ANI;

	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_DAGGER).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_DAGGER).second;
	//y = DAGGER_WEAPON_Y;
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
	if (checkInsideViewPort(viewport, viewport->WorldToScreen(D3DXVECTOR2(x, y))))
	{
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

DaggerWeapon::~DaggerWeapon()
{
}
