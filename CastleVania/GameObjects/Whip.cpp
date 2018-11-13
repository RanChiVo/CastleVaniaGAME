#include "Whip.h"
#include "../ResourceManagement.h"

constexpr int WHIT_ANI_HIT_RIGHT = 12;
constexpr int WHIT_ANI_HIT_LEFT = 13;

Whip::Whip(D3DXVECTOR2 position)
{
	x = position.x + 8;
	y = position.y + 18;

	LPANIMATION ani;

	ani = new Animation(150);
	ani->Add("AttackRight1");
	ani->Add("AttackRight2");
	ani->Add("AttackRight3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT, ani);

	ani = new Animation(150);
	ani->Add("AttackLeft1");
	ani->Add("AttackLeft2");
	ani->Add("AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT, ani);
	
	AddAnimation(WHIT_ANI_HIT_RIGHT);
	AddAnimation(WHIT_ANI_HIT_LEFT);

	currentAnimation = WHIT_ANI_HIT_RIGHT;
}

void Whip::draw(int direct, Viewport* viewport)
{
	if (direct)
	{
		currentAnimation = WHIT_ANI_HIT_RIGHT;
	}
	else currentAnimation = WHIT_ANI_HIT_LEFT;

	animations.find(currentAnimation)->second->SetLoop(true);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(pos.x, pos.y);
}

Whip::~Whip()
{
}
