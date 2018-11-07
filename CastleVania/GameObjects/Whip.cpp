#include "Whip.h"
#include "../ResourceManagement.h"


Whip::Whip(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y - 15;
	SetState(WHIP_HIT_STAND);
	ani = WHIT_ANI_HIT_STAND_RIGHT;
}

void Whip::loadResource()
{
	ResourceManagement*resourceManagement = ResourceManagement::GetInstance();

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add("AttackRight1");
	ani->Add("AttackRight2");
	ani->Add("AttackRight3");

	resourceManagement->Getanimations->Add(100, ani);

	GameObject::SetPosition(0.0f, 260);
}

void Whip::draw(int state, int direct)
{


	if (state == WHIP_HIT_STAND)
	{
		if (direct == 1)
		{
			ani = WHIT_ANI_HIT_STAND_RIGHT;
		}
		else
		{
			ani = WHIT_ANI_HIT_STAND_LEFT;
		}
	}
	else if (state == WHIT_HIT_SITDOWN)
	{
		if (direct == 1)
		{
			ani = WHIT_ANI_HIT_SITDOWN_RIGHT;
		}
		else
		{
			ani = WHIT_ANI_HIT_SITDOWN_LEFT;
		}
	}
	else if (state == WHIT_HIT_JUMP)
	{
		if (direct == 1)
		{
			ani = WHIT_ANI_HIT_JUMP_RIGHT;
		}
		else
		{
			ani = WHIT_ANI_HIT_JUMP_RIGHT;
		}
	}

	//if (GameObject::animations.find(ani)->second != nullptr)
	//{
		GameObject::animations.find(ani)->second->Render(x, y);
	//}
	//else return;
}

void Whip::SetStateWhip(int state)
{
	this->state = state;
}

Whip::~Whip()
{
}
