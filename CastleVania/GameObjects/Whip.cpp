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

	ani = new Animation(1000);
	ani->Add("1AttackRight1");
	ani->Add("1AttackRight1");
	ani->Add("1AttackRight2");
	ani->Add("1AttackRight3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT, ani);

	ani = new Animation(500);
	ani->Add("1AttackLeft1");
	ani->Add("1AttackLeft2");
	ani->Add("1AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT, ani);
	
	AddAnimation(WHIT_ANI_HIT_RIGHT);
	AddAnimation(WHIT_ANI_HIT_LEFT);

	currentAnimation = WHIT_ANI_HIT_RIGHT;
}

void Whip::updatePostision(D3DXVECTOR2 position, int currentFrameSimon, int currentAni)
{
	if(currentAni == SIMON_ANI_ATTACK_STANDING_RIGHT)
	switch (currentFrameSimon)
	{
	case 0:
		SetPosition(D3DXVECTOR2(position.x - 10 , position.y + 20));
		break;
	case 1:
		SetPosition(D3DXVECTOR2(position.x - 10, position.y + 20));
		break;
	case 2:
		SetPosition(D3DXVECTOR2(position.x , position.y));
		break;
	case 3:
		SetPosition(D3DXVECTOR2(position.x + 57, position.y + 15));
		break;
	default:
		break;
	}
	else  if (currentAni == SIMON_ANI_ATTACK_STANDING_LEFT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(position.x - 10, position.y + 20));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(position.x, position.y));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(position.x + 57, position.y + 15));
			break;
		default:
			break;
		}
	}
	else if (currentAni == SIMON_ANI_ATTACK_SITDOWN_RIGHT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(position.x - 10, position.y + 20));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(position.x, position.y));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(position.x + 57, position.y + 15));
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
			SetPosition(D3DXVECTOR2(position.x - 10, position.y + 20));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(position.x, position.y));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(position.x + 57, position.y + 15));
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

void Whip::draw(int direct, Viewport* viewport)
{
	if (direct)
	{
		currentAnimation = WHIT_ANI_HIT_RIGHT;
	}
	else currentAnimation = WHIT_ANI_HIT_LEFT;

	animations.find(currentAnimation)->second->SetLoop(true);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x,y));

	animations.find(currentAnimation)->second->Render(pos.x, pos.y);
}

Whip::~Whip()
{
}
