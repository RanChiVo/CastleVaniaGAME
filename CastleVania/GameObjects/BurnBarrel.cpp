#include "BurnBarrel.h"
#include "Simon.h"
#include "Whip.h"
#include "../Animations/Animations.h"
#include "../ResourceManagement.h"

constexpr int BURNBARREL_ANI = 22;


BurnBarrel::BurnBarrel()
{
}

BurnBarrel::BurnBarrel(D3DXVECTOR2 position)
{
	id = ID_TEX_BURNBARREL;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_BURNBARREL)->Get("Burn1")->getRect();
	int height = r.bottom - r.top;

	x = position.x;
	y = position.y - height;

	LPANIMATION ani;

	ani = new Animation(150);
	ani->Add("Burn1");
	ani->Add("Burn2");
	Animations::GetInstance()->Add(BURNBARREL_ANI, ani);


	AddAnimation(BURNBARREL_ANI);

	currentAnimation = BURNBARREL_ANI;
	nx = 1;
}

void BurnBarrel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
}

void BurnBarrel::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_BURNBARREL)->Get("Burn1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + height;
	bottom = y + width;
}

void BurnBarrel::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	Flip flip = flip_horiz;

	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

int BurnBarrel::getCurrentFrame()
{
	return animations.find(currentAnimation)->second->getCurrentFrame();
}

BurnBarrel::~BurnBarrel()
{
}
