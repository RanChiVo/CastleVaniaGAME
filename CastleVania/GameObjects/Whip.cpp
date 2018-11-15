#include "Whip.h"
#include "../ResourceManagement.h"
#include "Simon.h"
constexpr int WHIT_ANI_HIT_RIGHT = 12;
constexpr int WHIT_ANI_HIT_LEFT = 13;


Whip::Whip(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add("1AttackRight1");
	ani->Add("1AttackRight2");
	ani->Add("1AttackRight3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT, ani);

	ani = new Animation(200);
	ani->Add("1AttackLeft1");
	ani->Add("1AttackLeft2");
	ani->Add("1AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT, ani);

	AddAnimation(WHIT_ANI_HIT_RIGHT);
	AddAnimation(WHIT_ANI_HIT_LEFT);

	currentAnimation = WHIT_ANI_HIT_RIGHT;
}

void Whip::updatePostision(int currentFrameSimon, int currentAni)
{
	if (currentAni == SIMON_ANI_ATTACK_STANDING_RIGHT)
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x - 10, y + 20));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x, y));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x + 57, y + 15));
			break;
		default:
			break;
		}
	else if (currentAni == SIMON_ANI_ATTACK_SITDOWN_RIGHT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x - 10, y + 30));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x + 5, y + 30));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x + 57, y + 20));
			break;
		default:
			break;
		}
	}
	else if (currentAni == SIMON_ANI_ATTACK_STANDING_LEFT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x + 60, y + 15));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x + 30, y ));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x - 40, y + 13));
			break;
		default:
			break;
		}
	}
	else if (currentAni == SIMON_ANI_ATTACK_SITDOWN_LEFT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x + 60, y + 28 ));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x + 15, y + 20 ));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x - 40, y + 20));
			break;
		default:
			break;
		}
	}
}

int Whip::getframe()
{
	return animations.find(currentAnimation)->second->getCurrentFrame();
}

int Whip::getCurrentAnimation()
{
	return currentAnimation;
}

void Whip::draw(int direct, Viewport* viewport)
{
	if (direct == 1)
	{
		currentAnimation = WHIT_ANI_HIT_RIGHT;
	}
	else currentAnimation = WHIT_ANI_HIT_LEFT;

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(pos.x, pos.y);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

Whip::~Whip()
{
}
