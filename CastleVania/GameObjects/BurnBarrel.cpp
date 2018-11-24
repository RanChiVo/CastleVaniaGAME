#include "BurnBarrel.h"
#include "Simon.h"
#include "Whip.h"
#include "../Animations/Animations.h"
#include "../ResourceManagement.h"

constexpr int BURNBARREL_ANI = 20;
constexpr int BURNBARREL_ANI_EFFECT = 21;

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

	ani = new Animation(150);

	ani->Add("Effect1");
	ani->Add("Effect2");
	ani->Add("Effect3");
	ani->Add("Effect4");

	Animations::GetInstance()->Add(BURNBARREL_ANI_EFFECT, ani);

	AddAnimation(BURNBARREL_ANI);
	AddAnimation(BURNBARREL_ANI_EFFECT);

	state = BURNBARREL_STATE_NORMAL;
	currentAnimation = BURNBARREL_ANI;
}

void BurnBarrel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == BURNBARREL_STATE_NORMAL)
	{
		currentAnimation = BURNBARREL_ANI;
	}
	else if (state == BURNBARREL_STATE_EFFECT)
	{
		currentAnimation = BURNBARREL_ANI_EFFECT;
		
		if (animations.find(currentAnimation)->second->getCurrentFrame()== 3)

		animations.find(currentAnimation)->second->SetFinish(true);
	}
}

void BurnBarrel::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_BURNBARREL)->Get("Burn1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void BurnBarrel::Render(Viewport * viewport)
{
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(position.x, position.y);
}

int BurnBarrel::getCurrentFrame()
{
	return animations.find(currentAnimation)->second->getCurrentFrame();
}

BurnBarrel::~BurnBarrel()
{
}
