#include "BurnBarrel.h"
#include "../Animations/Animations.h"
#include "../ResourceManagement.h"
constexpr int BURNBARREL_ANI = 14;

BurnBarrel::BurnBarrel(D3DXVECTOR2 position)
{
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
}

void BurnBarrel::Render(Viewport * viewport)
{
	currentAnimation = BURNBARREL_ANI;
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->SetLoop(true);

	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(position.x, position.y);
}

BurnBarrel::~BurnBarrel()
{
}
